using System;
using System.Threading;

namespace PR_5
{
    internal class Program
    {
        private static readonly object _lock = new object();
        private static bool _dataReady = false;
        private static double _currentValue = 0;

        private static void Thread2_Generate()
        {
            try
            {
                double a = 2.0;
                double q = 1.5;
                double current = a;

                Console.WriteLine("[Thread2] Запуск генерации геометрической прогрессии");

                while (true)
                {
                    lock (_lock)
                    {
                        _currentValue = current;
                        _dataReady = true;
                    }

                    Console.WriteLine($"[Thread2] Сгенерировано: {current:F2}");

                    // Условие приостановки
                    if (Math.Abs(current) >= 1000)
                    {
                        Console.WriteLine("[Thread2] Значение >= 1000 → приостановка на 5 сек");
                        Thread.Sleep(5000);
                        Console.WriteLine("[Thread2] Возобновление после паузы");
                    }

                    current *= q;
                    Thread.Sleep(300);
                }
            }
            catch (ThreadAbortException)
            {
                Console.WriteLine("[Thread2] Получен Abort → аварийное завершение потока");
            }
        }

        private static void Thread1_Display()
        {
            Console.WriteLine("[Thread1] Запуск вывода данных");

            while (true)
            {
                lock (_lock)
                {
                    if (_dataReady)
                    {
                        Console.WriteLine($"[Thread1] Получено: {_currentValue:F2}");
                        _dataReady = false;
                    }
                }
                Thread.Sleep(100);
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("ПЗ 5. Блокировка и аварийное завершение потоков\n");

            Thread thread2 = new Thread(Thread2_Generate)
            {
                Name = "Генератор прогрессии"
            };

            Thread thread1 = new Thread(Thread1_Display)
            {
                Name = "Вывод на консоль"
            };

            thread1.Start();
            thread2.Start();

            Thread.Sleep(15000);

            Console.WriteLine("\n[Main] Запрос аварийного завершения Thread2...");
            thread2.Abort();     

            thread2.Join();    
        }
    }
}