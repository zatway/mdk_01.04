using System;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Storage;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PZ_25
{
    public sealed partial class App : Application
    {
        public App()
        {
            this.InitializeComponent();
            this.Suspending += OnSuspending;
            this.Resuming += OnResuming;
        }

        protected override void OnLaunched(LaunchActivatedEventArgs e)
        {
            string stateMsg = $"OnLaunched\nПредыдущее состояние: {e.PreviousExecutionState}";

            if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
            {
                stateMsg += "\n→ Приложение было завершено системой (нехватка памяти и т.п.)";
                stateMsg += "\n→ Можно восстановить сохранённые данные";
            }
            else if (e.PreviousExecutionState == ApplicationExecutionState.ClosedByUser)
            {
                stateMsg += "\n→ Пользователь закрыл приложение вручную";
            }
            else if (e.PreviousExecutionState == ApplicationExecutionState.NotRunning)
            {
                stateMsg += "\n→ Первый запуск или после перезагрузки";
            }

            ShowMessageAsync(stateMsg);

            Frame rootFrame = Window.Current.Content as Frame;

            if (rootFrame == null)
            {
                rootFrame = new Frame();
                rootFrame.NavigationFailed += OnNavigationFailed;
                Window.Current.Content = rootFrame;
            }

            if (e.PrelaunchActivated == false)
            {
                if (rootFrame.Content == null)
                {
                    rootFrame.Navigate(typeof(MainPage), e.Arguments);
                }
                Window.Current.Activate();
            }
        }

        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();

            string msg = $"Suspending — приложение приостанавливается\nВремя: {DateTime.Now:HH:mm:ss}";
            ShowMessageAsync(msg);

            if (Window.Current.Content is Frame frame && frame.Content is MainPage page)
            {
                ApplicationData.Current.LocalSettings.Values["SavedTotal"] = page.CurrentTotal;
            }

            deferral.Complete();
        }

        private void OnResuming(object sender, object e)
        {
            string msg = $"Resuming — приложение возобновляется\nВремя: {DateTime.Now:HH:mm:ss}";
            ShowMessageAsync(msg);
        }

        private async void ShowMessageAsync(string text)
        {
            try
            {
                var dialog = new MessageDialog(text, "Состояние приложения");
                await dialog.ShowAsync();
            }
            catch
            {
                // Если UI-поток занят — пишем только в отладку
                System.Diagnostics.Debug.WriteLine(text);
            }
        }

        void OnNavigationFailed(object sender, Windows.UI.Xaml.Navigation.NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }
    }
}