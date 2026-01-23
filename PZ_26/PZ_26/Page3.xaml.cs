using Windows.Devices.Enumeration;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace PZ_26
{
    public sealed partial class Page3 : Page
    {
        public Page3()
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
            Frame.Navigate(typeof(Page1), "Переход со страницы 3");
        }

        private void BtnPage2_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Page2), "Переход со страницы 3");
        }
    }
}