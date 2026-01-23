using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_26
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void BtnPage1_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page1), "Переход с главной страницы");
        }

        private void BtnPage2_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page2), "Переход с главной страницы");
        }

        private void BtnPage3_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page3), "Переход с главной страницы");
        }
    }
}