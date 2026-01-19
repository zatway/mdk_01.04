using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_22
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a <see cref="Frame">.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            InitializeComponent();
            UpdateTotal(null, null);
        }

        private void UpdateTotal(object sender, RoutedEventArgs e)
        {
            int total = 0;

            if (chkCola.IsChecked == true) total += Int32.Parse(chkCola.Tag?.ToString());
            if (chkFanta.IsChecked == true) total += Int32.Parse(chkFanta.Tag?.ToString());
            if (chkSprite.IsChecked == true) total += Int32.Parse(chkSprite.Tag?.ToString());
            if (chk7Up.IsChecked == true) total += Int32.Parse(chk7Up.Tag?.ToString());
            if (chkMirinda.IsChecked == true) total += Int32.Parse(chkMirinda.Tag?.ToString());

            if (chkIce.IsChecked == true) total += Int32.Parse(chkIce.Tag?.ToString());
            if (chkLemon.IsChecked == true) total += Int32.Parse(chkLemon.Tag?.ToString());
            if (chkMint.IsChecked == true) total += Int32.Parse(chkMint.Tag?.ToString());
            if (chkSyrup.IsChecked == true) total += Int32.Parse(chkSyrup.Tag?.ToString());

            tbTotal.Text = $"{total} ₽";
        }
    }
}
