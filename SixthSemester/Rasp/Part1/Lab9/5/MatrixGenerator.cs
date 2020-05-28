using System;

namespace Lab9_5
{
    public class MatrixGenerator
    {
        private readonly int _rowSize;
        private readonly int _columnSize;
        private readonly double _maxValue;

        private readonly Random _random;
        
        public MatrixGenerator(int size, double maxValue):this(size,size,maxValue){
        }

        public MatrixGenerator(int rowSize, int columnSize, double maxValue)
        {
            this._rowSize = rowSize;
            this._columnSize = columnSize;
            this._maxValue = maxValue;

            _random = new Random();
        }

        public double[,] Generate()
        {
            var matrix=new double[_rowSize,_columnSize];

            for (var i = 0; i < _rowSize; i++)
            {
                for (var j = 0; j < _columnSize; j++)
                {
                    matrix[i, j] = _maxValue*_random.NextDouble();
                }
            }
            
            return matrix;
        }
    }
}