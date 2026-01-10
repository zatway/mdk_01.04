using System;
using System.Runtime.InteropServices;

namespace PR_6_Memory
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    public struct MEMORYSTATUSEX
    {
        public uint dwLength;
        public uint dwMemoryLoad;
        public ulong ullTotalPhys;
        public ulong ullAvailPhys;
        public ulong ullTotalPageFile;
        public ulong ullAvailPageFile;
        public ulong ullTotalVirtual;
        public ulong ullAvailVirtual;
        public ulong ullAvailExtendedVirtual;
    }

    class Program
    {
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool GlobalMemoryStatusEx(ref MEMORYSTATUSEX lpBuffer);

        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            MEMORYSTATUSEX memStatus = new MEMORYSTATUSEX();
            memStatus.dwLength = (uint)Marshal.SizeOf(typeof(MEMORYSTATUSEX));

            if (GlobalMemoryStatusEx(ref memStatus))
            {
                Console.WriteLine($"Физическая память:");
                Console.WriteLine($"Процент используемой физической памяти: {memStatus.dwMemoryLoad}%");

                Console.WriteLine($"Всего: {FormatBytes(memStatus.ullTotalPhys)}");
                Console.WriteLine($"Доступно: {FormatBytes(memStatus.ullAvailPhys)}");
                Console.WriteLine($"Используется: {FormatBytes(memStatus.ullTotalPhys - memStatus.ullAvailPhys)}");
                Console.WriteLine();

                Console.WriteLine($"Файл подкачки:");
                Console.WriteLine($"Всего: {FormatBytes(memStatus.ullTotalPageFile)}");
                Console.WriteLine($"Доступно: {FormatBytes(memStatus.ullAvailPageFile)}");
                Console.WriteLine();

                Console.WriteLine($"Виртуальная память:");
                Console.WriteLine($"Всего: {FormatBytes(memStatus.ullTotalVirtual)}");
                Console.WriteLine($"Доступно: {FormatBytes(memStatus.ullAvailVirtual)}");
                Console.WriteLine();
            }
            else
            {
                Console.WriteLine($"Ошибка вызова GlobalMemoryStatusEx: {Marshal.GetLastWin32Error()}");
            }
        }

        private static string FormatBytes(ulong bytes)
        {
            double value = bytes / 1024 / 1024;
            return $"{value:0.##} МБ";
        }
    }
}