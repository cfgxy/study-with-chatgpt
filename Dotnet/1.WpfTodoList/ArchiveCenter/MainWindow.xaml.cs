using ArchiveCenter.Data;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;

namespace ArchiveCenter
{
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public ICommand CheckBoxCheckedCommand { get; }

        // 数据库ORM
        private TodoContext todoContext;

        // Tasks，界面上列表框的双向绑定
        private ObservableCollection<TodoItem> tasks;
        public ObservableCollection<TodoItem> Tasks
        {
            get { return tasks; }
            set
            {
                tasks = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Tasks)));
            }
        }

        // NewTask属性，界面上输入框的双向绑定
        private string newTask;
        public string NewTask
        {
            get { return newTask; }
            set
            {
                newTask = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(NewTask)));
            }
        }

        // 构造函数，逻辑或阻塞代码尽量放到Window_Loaded，这里只做简单属性初始化
        public MainWindow()
        {
            // 加载Xaml界面
            InitializeComponent();
            DataContext = this;
            CheckBoxCheckedCommand = new RelayCommand(CheckBox_Checked);
        }

        // 窗口加载时初始化逻辑
        private void Window_Loaded(object sender, EventArgs e)
        {
            todoContext = new TodoContext();
            todoContext.Database.Migrate();
            Tasks = new ObservableCollection<TodoItem>(todoContext.TodoItems);
        }

        // 窗口关闭时执行清理逻辑
        private void Window_Closed(object sender, EventArgs e)
        {
            todoContext.Dispose();
        }

        // 添加按钮响应事件
        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrEmpty(NewTask))
            {
                TodoItem task = new TodoItem { Task = NewTask };
                Tasks.Add(task);
                todoContext.TodoItems.Add(task);
                todoContext.SaveChanges();
                NewTask = string.Empty;
            }
        }

        // 列表复选框响应事件
        private void CheckBox_Checked(object parameter)
        {
            if (parameter is TodoItem todoItem) {
                todoContext.SaveChanges();
            }
        }

        // 删除按钮响应事件
        private void DeleteButton_Click(object sender, RoutedEventArgs e)
        {
            if (lstTasks.SelectedItem is TodoItem selectedTask)
            {
                Tasks.Remove(selectedTask);
                todoContext.TodoItems.Remove(selectedTask);
                todoContext.SaveChanges();
            }
        }
    }
}

