using System;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_25
{
    public sealed partial class MainPage : Page
    {
        public int CurrentTotal { get; private set; } = 0;

        public MainPage()
        {
            this.InitializeComponent();

            var localSettings = ApplicationData.Current.LocalSettings;
            if (localSettings.Values.TryGetValue("SavedTotal", out object saved) && saved is int total)
            {
                CurrentTotal = total;
                tbTotal.Text = $"{total} ₽";

                ShowMessageAsync($"Восстановлена сумма: {total} ₽ (приложение было Terminated)");
            }
            else
            {
                UpdateTotal(null, null);
            }
        }

        public void UpdateTotal(object sender, RoutedEventArgs e)
        {
            int total = 0;

            if (chkCola.IsChecked == true) total += GetTagValue(chkCola);
            if (chkFanta.IsChecked == true) total += GetTagValue(chkFanta);
            if (chkSprite.IsChecked == true) total += GetTagValue(chkSprite);
            if (chk7Up.IsChecked == true) total += GetTagValue(chk7Up);
            if (chkMirinda.IsChecked == true) total += GetTagValue(chkMirinda);

            if (chkIce.IsChecked == true) total += GetTagValue(chkIce);
            if (chkLemon.IsChecked == true) total += GetTagValue(chkLemon);
            if (chkMint.IsChecked == true) total += GetTagValue(chkMint);
            if (chkSyrup.IsChecked == true) total += GetTagValue(chkSyrup);

            CurrentTotal = total;
            tbTotal.Text = $"{total} ₽";
        }

        private int GetTagValue(CheckBox checkBox)
        {
            if (checkBox.Tag is string tagStr && int.TryParse(tagStr, out int value))
                return value;
            return 0;
        }

        private async void ShowMessageAsync(string text)
        {
            try
            {
                var dialog = new MessageDialog(text, "Восстановление заказа");
                await dialog.ShowAsync();
            }
            catch { }
        }
    }
}