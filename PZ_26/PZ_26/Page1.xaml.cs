using Windows.Devices.Enumeration;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace PZ_26
{
    public sealed partial class Page1 : Page
    {
        public Page1()
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

        private void BtnPage2_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page2), "Переход со страницы 1");
        }

        private void BtnPage3_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page3), "Переход со страницы 1");
        }
    }
}