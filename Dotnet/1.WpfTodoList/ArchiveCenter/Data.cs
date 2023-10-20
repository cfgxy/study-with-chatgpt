using Microsoft.EntityFrameworkCore;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;

namespace ArchiveCenter.Data
{
    public class TodoItem: INotifyPropertyChanged
    {
        [Key]
        public int Id { get; set; }
        public string Task { get; set; }

        private bool isCompleted;
        public bool IsCompleted {
            get { return isCompleted; }
            set {
                isCompleted = value;
                OnPropertyChanged(nameof(IsCompleted));
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class TodoContext : DbContext
    {
        public DbSet<TodoItem> TodoItems { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=TodoList.db");
            base.OnConfiguring(optionsBuilder);
        }
    }

    /*
    public class TodoItemDatabase
    {
        private const string DatabaseFileName = "TodoList.db";
        private const string ConnectionString = "Data Source=" + DatabaseFileName;

        public TodoItemDatabase()
        {
            if (!File.Exists(DatabaseFileName))
            {
                SQLiteConnection.CreateFile(DatabaseFileName);
                CreateTodoTable();
            }
        }

        private void CreateTodoTable()
        {
            using (var connection = new SQLiteConnection(ConnectionString))
            {
                connection.Open();
                using (var command = new SQLiteCommand(connection))
                {
                    command.CommandText = "CREATE TABLE IF NOT EXISTS TodoItems (Id INTEGER PRIMARY KEY AUTOINCREMENT, Task TEXT, IsCompleted INTEGER)";
                    command.ExecuteNonQuery();
                }
            }
        }

        public List<TodoItem> GetTodoItems()
        {
            var todoItems = new List<TodoItem>();
            using (var connection = new SQLiteConnection(ConnectionString))
            {
                connection.Open();
                using (var command = new SQLiteCommand(connection))
                {
                    command.CommandText = "SELECT * FROM TodoItems";
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            var todoItem = new TodoItem
                            {
                                Id = reader.GetInt32(0),
                                Task = reader.GetString(1),
                                IsCompleted = reader.GetBoolean(2)
                            };
                            todoItems.Add(todoItem);
                        }
                    }
                }
            }
            return todoItems;
        }

        public void InsertTodoItem(TodoItem todoItem)
        {
            using (var connection = new SQLiteConnection(ConnectionString))
            {
                connection.Open();
                using (var command = new SQLiteCommand(connection))
                {
                    command.CommandText = "INSERT INTO TodoItems (Task, IsCompleted) VALUES (@Task, @IsCompleted)";
                    command.Parameters.AddWithValue("@Task", todoItem.Task);
                    command.Parameters.AddWithValue("@IsCompleted", todoItem.IsCompleted);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void UpdateTodoItem(TodoItem todoItem)
        {
            using (var connection = new SQLiteConnection(ConnectionString))
            {
                connection.Open();
                using (var command = new SQLiteCommand(connection))
                {
                    command.CommandText = "UPDATE TodoItems SET Task = @Task, IsCompleted = @IsCompleted WHERE Id = @Id";
                    command.Parameters.AddWithValue("@Task", todoItem.Task);
                    command.Parameters.AddWithValue("@IsCompleted", todoItem.IsCompleted);
                    command.Parameters.AddWithValue("@Id", todoItem.Id);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void DeleteTodoItem(TodoItem todoItem)
        {
            using (var connection = new SQLiteConnection(ConnectionString))
            {
                connection.Open();
                using (var command = new SQLiteCommand(connection))
                {
                    command.CommandText = "DELETE FROM TodoItems WHERE Id = @Id";
                    command.Parameters.AddWithValue("@Id", todoItem.Id);
                    command.ExecuteNonQuery();
                }
            }
        }
    }
    */

}
