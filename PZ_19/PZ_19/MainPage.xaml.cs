using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_19
{
    public sealed partial class MainPage : Page
    {
        private double _firstNumber = 0;
        private string _operation = "";
        private bool _isNewInput = true;      // Флаг: начинаем ли мы вводить новое число
        private bool _resultShown = false;    // Флаг: показан ли результат (чтобы очистить экран при след. вводе)

        public MainPage()
        {
            this.InitializeComponent();
        }

        private void Number_Click(object sender, RoutedEventArgs e)
        {
            string digit = (sender as Button).Content.ToString();

            if (_resultShown)
            {
                FullClear();
                _resultShown = false;
            }

            if (_isNewInput || Display.Text == "0" || Display.Text == "Ошибка")
            {
                Display.Text = digit;
                _isNewInput = false;
            }
            else
            {
                Display.Text += digit;
            }
        }

        private void Operation_Click(object sender, RoutedEventArgs e)
        {
            if (Display.Text == "0" && string.IsNullOrEmpty(_operation)) return;
            if (Display.Text == "Ошибка") return;

            string op = (sender as Button).Content.ToString();

            if (double.TryParse(Display.Text, out double currentNum))
            {
                // Унарная операция √ (считается мгновенно)
                if (op == "√")
                {
                    if (currentNum < 0) { ShowError("Недопустимый ввод"); return; }
                    double res = Math.Sqrt(currentNum);
                    HistoryDisplay.Text = $"√({currentNum})";
                    Display.Text = res.ToString();
                    _resultShown = true;
                    return;
                }

                // Бинарные операции (+, -, *, /, ^)
                _firstNumber = currentNum;
                _operation = op;
                _isNewInput = true;
                _resultShown = false;
                HistoryDisplay.Text = $"{_firstNumber} {_operation}";
            }
        }

        private void Equal_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(_operation) || _resultShown) return;

            if (double.TryParse(Display.Text, out double secondNumber))
            {
                double result = 0;
                bool isError = false;

                switch (_operation)
                {
                    case "+": result = _firstNumber + secondNumber; break;
                    case "-": result = _firstNumber - secondNumber; break;
                    case "*": result = _firstNumber * secondNumber; break;
                    case "/":
                        if (secondNumber == 0) isError = true;
                        else result = _firstNumber / secondNumber;
                        break;
                    case "^": result = Math.Pow(_firstNumber, secondNumber); break;
                }

                if (isError)
                {
                    ShowError("Деление на 0");
                }
                else
                {
                    HistoryDisplay.Text = $"{_firstNumber} {_operation} {secondNumber} =";
                    Display.Text = result.ToString();
                    _operation = "";
                    _resultShown = true; // Теперь при клике на цифру экран очистится
                }
            }
        }

        // Логика смены знака (+/-)
        private void PlusMinus_Click(object sender, RoutedEventArgs e)
        {
            if (Display.Text == "0" || Display.Text == "Ошибка") return;

            if (Display.Text.StartsWith("-"))
                Display.Text = Display.Text.Substring(1);
            else
                Display.Text = "-" + Display.Text;
        }

        private void Clear_Click(object sender, RoutedEventArgs e) => FullClear();

        private void FullClear()
        {
            Display.Text = "0";
            HistoryDisplay.Text = "";
            _firstNumber = 0;
            _operation = "";
            _isNewInput = true;
            _resultShown = false;
        }

        private void ShowError(string msg)
        {
            Display.Text = "Ошибка";
            HistoryDisplay.Text = msg;
            _resultShown = true;
        }
    }
}