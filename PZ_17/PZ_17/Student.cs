using System;
using System.Collections.Generic;
using System.Text;

namespace PZ_17
{
    public class Student
    {
        public string Name { get; set; }
        public string Group { get; set; }

        public override string ToString()
        {
            return $"студент {this.Name} из группы {this.Group}";
        }
    }
}
