using System;
using System.Threading;

namespace PR_4
{
    public class Database
    {
        private readonly object _lockObject = new object();

        public void SaveData(string text)
        {
            Console.WriteLine($"{Thread.CurrentThread.Name} - SaveData - Started");

            Console.WriteLine($"{Thread.CurrentThread.Name} - SaveData - working");

            for (int i = 0; i < 5; i++)
            {
                Console.Write(text);
                Thread.Sleep(350);
            }

            Console.WriteLine();
            Console.WriteLine($"{Thread.CurrentThread.Name} - SaveData - ended");
        }
    }

    class Program
    {
        public static Database db = new Database();

        static void WorkerThreadMethod1()
        {
            Console.WriteLine($"{Thread.CurrentThread.Name} - started");
            Console.WriteLine($"{Thread.CurrentThread.Name} - Calling Database.SaveData");

            db.SaveData("x");

            Console.WriteLine($"{Thread.CurrentThread.Name} - Returned from SaveData");
        }

        static void WorkerThreadMethod2()
        {
            Console.WriteLine($"{Thread.CurrentThread.Name} - started");
            Console.WriteLine($"{Thread.CurrentThread.Name} - Calling Database.SaveData");

            db.SaveData("0");

            Console.WriteLine($"{Thread.CurrentThread.Name} - Returned from SaveData");
        }

        static void Main(string[] args)
        {
            Console.WriteLine("main - creating worker threads\n");

            Thread t1 = new Thread(WorkerThreadMethod1)
            {
                Name = "worker thread #1"
            };

            Thread t2 = new Thread(WorkerThreadMethod2)
            {
                Name = "worker thread #2"
            };

            t1.Start();
            t2.Start();

            t1.Join();
            t2.Join();

            Console.WriteLine("\nВсе потоки завершили работу.");
        }
    }
}