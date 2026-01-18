using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_17
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a <see cref="Frame">.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            button2.Content = "успешно!";
        }
    }
}
