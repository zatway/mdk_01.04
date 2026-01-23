using System;
using System.Linq;
using Windows.Media.Import;
using Windows.System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace PZ_24
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

        private void txtUrl_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == VirtualKey.Enter)
            {
                NavigateToUrl();
                e.Handled = true;
            }
        }

        private void BtnGo_Click(object sender, RoutedEventArgs e)
        {
            NavigateToUrl();
        }

        private void NavigateToUrl()
        {
            string url = txtUrl.Text.Trim();
            if (string.IsNullOrWhiteSpace(url)) return;

            if (!url.StartsWith("http://") && !url.StartsWith("https://"))
            {
                url = "https://" + url;
            }
 
            webView.Source = new Uri(url);
          
        }

        private void BtnAddBookmark_Click(object sender, RoutedEventArgs e)
        {
            string url = webView.Source?.ToString();
            string title = webView.DocumentTitle;
            if (string.IsNullOrEmpty(url)) return;

            string bookmarkName = string.IsNullOrWhiteSpace(title) ? url : title;

            var item = new MenuFlyoutItem
            {
                Text = bookmarkName.Length > 60 ? bookmarkName.Substring(0, 57) + "..." : bookmarkName,
                Tag = url
            };

            item.Click += BookmarkItem_Click;

            BookmarksMenu.Items.Add(item);
        }

        private void BookmarkItem_Click(object sender, RoutedEventArgs e)
        {
            if (sender is MenuFlyoutItem item && item.Tag is string url)
            {
                txtUrl.Text = url;
                webView.Source = new Uri(url);
            }
        }

        private void WebView_NavigationCompleted(WebView sender, WebViewNavigationCompletedEventArgs args)
        {
            if (args.IsSuccess && sender.Source != null)
            {
                txtUrl.Text = sender.Source.ToString();
            }
        }
    }
}
