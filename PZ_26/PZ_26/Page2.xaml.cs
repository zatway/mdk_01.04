using Windows.Devices.Enumeration;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace PZ_26
{
    public sealed partial class Page2 : Page
    {
        public Page2()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter != null)
            {
                tbMessage.Text = e.Parameter.ToString();
            }
        }

        private void BtnHome_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }

        private void BtnPage1_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page1), "Переход со страницы 2");
        }

        private void BtnPage3_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page3), "Переход со страницы 2");
        }
    }
}