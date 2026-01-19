using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_21
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a <see cref="Frame">.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private void btnSubmit_Click(object sender, RoutedEventArgs e)
        {
            string name = txtName.Text.Trim();
            if (!string.IsNullOrEmpty(name))
            {
                tbGreeting.Text = $"Привет, {name}";
                tbGreeting.Visibility = Visibility.Visible;
            }
        }
    }
}
