using System;
using System.Threading;

namespace PZ_20
{
    class Program
    {
        static void Main(string[] args)
        {
            const int PUMP_COUNT = 4;
            const int CAR_COUNT = 10; 

            var pumpSemaphore = new Semaphore(PUMP_COUNT, PUMP_COUNT);

            Console.WriteLine($"Колонок: {PUMP_COUNT}. Машины в очереди: {CAR_COUNT}\n");

            for (int i = 1; i <= CAR_COUNT; i++)
            {
                int carNumber = i;
                var car = new Thread(() => CarRefuel(carNumber, pumpSemaphore));
                car.Name = $"Машина {carNumber}";
                car.Start();
            }

            Console.WriteLine("\nВсе машины в очереди или заправляются\n");
        }

        static void CarRefuel(int number, Semaphore semaphore)
        {
            string name = $"Машина {number}";

            Console.WriteLine($"{name} подъехала к АЗС");

            semaphore.WaitOne();

            try
            {
                Console.WriteLine($"{name} начала заправку");

                int refuelTime = 1500;
                Thread.Sleep(refuelTime);

                Console.WriteLine($"{name} заправилась за {refuelTime} мс");
            }
            finally
            {
                Console.WriteLine($"{name} освободила колонку\n");
                semaphore.Release();
            }
        }
    }
}