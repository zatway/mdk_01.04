using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_18
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a <see cref="Frame">.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            StatusTextBox.Text = "Панель закрыта";
        }

        private void TogglePaneButton_Click(object sender, RoutedEventArgs e)
        {
            MainSplitView.IsPaneOpen = !MainSplitView.IsPaneOpen;

            if (MainSplitView.IsPaneOpen)
            {
                StatusTextBox.Text = "Панель активирована!";
                TogglePaneButton.Content = "Закрыть панель";
            }
            else
            {
                StatusTextBox.Text = "Панель закрыта";
                TogglePaneButton.Content = "Открыть панель";
            }
        }
    }
}
