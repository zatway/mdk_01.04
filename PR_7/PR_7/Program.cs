using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;

namespace Lab_Threads_Heap_VMMAP
{
    class Program
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr HeapCreate(uint flOptions, UIntPtr dwInitialSize, UIntPtr dwMaximumSize);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool HeapDestroy(IntPtr hHeap);

        static void Main(string[] args)
        {
            Console.WriteLine($"PID процесса: {Process.GetCurrentProcess().Id}");
            Console.WriteLine("Запуск фоновых потоков...");
            StartWorkerThreads();
            Console.ReadLine();

            IntPtr customHeap = HeapCreate(
                0,                      
                (UIntPtr)(100UL * 1024 * 1024),  
                UIntPtr.Zero      
            );

            if (customHeap != IntPtr.Zero)
            {
                Console.WriteLine($"\nСоздан дополнительный Heap: 0x{customHeap:X16}");
            }
            else
            {
                Console.WriteLine($"Ошибка HeapCreate: {Marshal.GetLastWin32Error()}");
            }

            Console.WriteLine("\nНажмите Enter для завершения программы...");
            Console.ReadLine();

            if (customHeap != IntPtr.Zero)
            {
                HeapDestroy(customHeap);
                Console.WriteLine("Дополнительный Heap уничтожен");
            }
        }

        static void StartWorkerThreads()
        {
            new Thread(() =>
            {
                Thread.CurrentThread.Name = "Idle-Spin";
                while (true)
                {
                    Thread.SpinWait(40_000_000);
                    Thread.Sleep(1);
                }
            })
            { IsBackground = true }.Start();

            new Thread(() =>
            {
                Thread.CurrentThread.Name = "Memory-Eater";
                var random = new Random();
                var list = new List<byte[]>();

                while (true)
                {
                    try
                    {
                        int sizeKb = random.Next(400, 6000);
                        list.Add(new byte[sizeKb * 1024]);

                        if (list.Count > 150)
                            list.RemoveAt(0);
                    }
                    catch
                    {
                        Thread.Sleep(500);
                    }

                    Thread.Sleep(150);
                }
            })
            { IsBackground = true }.Start();
        }
    }
}