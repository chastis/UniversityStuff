using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace Lab9_5
{
    public class Test
    {
        private List<int> sizes;
        private HtmlBuilder _builder;

        public Test(string path)
        {
            _builder = new HtmlBuilder(path);
            _builder.CreateHtml().AddHead().CreateTable();

            this.sizes = new List<int>();
        }

        public void AddTask(int size)
        {
            sizes.Add(size);
        }

        public void Run()
        {
            double sequentialTime;
            double time, acceleration;
            List<KeyValuePair<double, double>> results;
            foreach (var i in sizes)
            {
                DateTime t2 = DateTime.Now;
                results = new List<KeyValuePair<double, double>>();
                sequentialTime = Calculate(i, 1) / 1000.0;

                time = Calculate(i, 2) / 1000.0;
                acceleration = sequentialTime / time;
                results.Add(new KeyValuePair<double, double>(time, acceleration));

                time = Calculate(i, 4) / 1000.0;
                acceleration = sequentialTime / time;
                results.Add(new KeyValuePair<double, double>(time, acceleration));

                _builder.AddResult(i, sequentialTime, results);

                Console.WriteLine("N = "+i+"; time = "+(DateTime.Now-t2));
            }
            

            Finish();
        }

        private int Calculate(int size, int threadsNumber)
        {
            var matrixGenerator = new MatrixGenerator(size, 100);
            var A = matrixGenerator.Generate();
            var B = matrixGenerator.Generate();

            var stripesSchema = new StripesSchema(A, B, threadsNumber);
            var stopwatch = new Stopwatch();
            stopwatch.Start();

            var C = stripesSchema.CalculateProduct();

            stopwatch.Stop();

            return stopwatch.Elapsed.Milliseconds;
        }

        private void Finish()
        {
            _builder.FinishTable().Finish();
        }
    }
}