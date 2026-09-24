using System;
using System.Collections.Generic;

namespace StoreManagement
{
    // 1. Класс Товар (Product)
    public class Product
    {
        // Поля с разными модификаторами доступа
        private string name;
        private decimal price;
        private int quantity;
        protected string category;
        internal string description;

        // Геттеры и сеттеры (Свойства)
        public string Name
        {
            get => name;
            set => name = value;
        }

        public decimal Price
        {
            get => price;
            set => price = value >= 0 ? value : 0;
        }

        public int Quantity
        {
            get => quantity;
            set => quantity = value >= 0 ? value : 0;
        }

        public string Category
        {
            get => category;
            set => category = value;
        }

        public string Description
        {
            get => description;
            set => description = value;
        }

        // Конструктор
        public Product(string name, decimal price, int quantity, string category, string description)
        {
            Name = name;
            Price = price;
            Quantity = quantity;
            Category = category;
            Description = description;
        }

        // Методы
        public decimal GetTotalPrice()
        {
            return price * quantity;
        }

        public void UpdateQuantity(int amount)
        {
            quantity += amount;
            if (quantity < 0) quantity = 0;
        }

        public string GetProductInfo()
        {
            return $"Товар: {name} | Категория: {category} | Цена: {price:C} | Кол-во: {quantity} | Описание: {description}";
        }
    }

    // 2. Класс Продавец (Seller)
    public class Seller
    {
        // Поля
        private string name;
        private string employeeId;
        protected decimal salary;
        internal string contactInfo;

        // Список товаров продавца
        private List<Product> products = new List<Product>();

        // Геттеры и сеттеры
        public string Name
        {
            get => name;
            set => name = value;
        }

        public string EmployeeId
        {
            get => employeeId;
            set => employeeId = value;
        }

        public decimal Salary
        {
            get => salary;
            set => salary = value >= 0 ? value : 0;
        }

        public string ContactInfo
        {
            get => contactInfo;
            set => contactInfo = value;
        }

        public List<Product> Products => products;

        // Конструктор
        public Seller(string name, string employeeId, decimal salary, string contactInfo)
        {
            Name = name;
            EmployeeId = employeeId;
            Salary = salary;
            ContactInfo = contactInfo;
        }

        // Методы
        public void AddProduct(Product product)
        {
            if (product != null)
            {
                products.Add(product);
                Console.WriteLine($"Товар '{product.Name}' добавлен продавцу {name}.");
            }
        }

        public void SellProduct(Product product, int quantity)
        {
            if (product != null && products.Contains(product))
            {
                if (product.Quantity >= quantity)
                {
                    product.UpdateQuantity(-quantity);
                    Console.WriteLine($"Продавец {name} продал {quantity} шт. товара '{product.Name}'.");
                }
                else
                {
                    Console.WriteLine($"Недостаточно товара '{product.Name}' на складе!");
                }
            }
            else
            {
                Console.WriteLine($"Товар '{product?.Name}' не найден у продавца {name}.");
            }
        }

        public string GetSellerInfo()
        {
            return $"Продавец: {name} (ID: {employeeId}) | З/П: {salary:C} | Контакты: {contactInfo}";
        }
    }

    // 3. Класс Магазин (Store)
    public class Store
    {
        // Поля
        private string storeName;
        private string location;
        public string storeHours;

        // Списки продавцов и товаров магазина
        private List<Seller> sellers = new List<Seller>();
        private List<Product> products = new List<Product>();

        // Геттеры и сеттеры
        public string StoreName
        {
            get => storeName;
            set => storeName = value;
        }

        public string Location
        {
            get => location;
            set => location = value;
        }

        public List<Seller> Sellers => sellers;
        public List<Product> Products => products;

        // Конструктор
        public Store(string storeName, string location, string storeHours)
        {
            StoreName = storeName;
            Location = location;
            this.storeHours = storeHours;
        }

        // Методы
        public void AddSeller(Seller seller)
        {
            if (seller != null)
            {
                sellers.Add(seller);
                Console.WriteLine($"Продавец {seller.Name} нанят в магазин '{storeName}'.");
            }
        }

        public void AddProduct(Product product)
        {
            if (product != null)
            {
                products.Add(product);
            }
        }

        public void ListProducts()
        {
            Console.WriteLine($"\n--- Список товаров в магазине '{storeName}' ---");
            if (products.Count == 0)
            {
                Console.WriteLine("Товары отсутствуют.");
                return;
            }

            foreach (var product in products)
            {
                Console.WriteLine(product.GetProductInfo());
            }
        }

        public string GetStoreInfo()
        {
            return $"Магазин: '{storeName}' | Адрес: {location} | Часы работы: {storeHours}";
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            // Создаем по одному экземпляру каждого класса
            Product laptop = new Product("Ноутбук", 75000m, 10, "Электроника", "Игровой ноутбук 16 ГБ ОЗУ");
            Seller sellerJohn = new Seller("Иван Иванов", "EMP-101", 50000m, "ivan@store.com");
            Store techStore = new Store("ТехноМир", "ул. Ленина, д. 10", "09:00 - 21:00");

            // Связываем объекты между собой
            techStore.AddSeller(sellerJohn);
            sellerJohn.AddProduct(laptop);
            techStore.AddProduct(laptop);

            // Вывод информации об объектах
            Console.WriteLine("\n--- Информация об объектах ---");
            Console.WriteLine(techStore.GetStoreInfo());
            Console.WriteLine(sellerJohn.GetSellerInfo());
            Console.WriteLine(laptop.GetProductInfo());
            Console.WriteLine($"Общая стоимость на складе: {laptop.GetTotalPrice():C}");

            // Демонстрация работы методов
            Console.WriteLine("\n--- Продажа товара ---");
            sellerJohn.SellProduct(laptop, 3);
            Console.WriteLine($"Остаток товара: {laptop.Quantity} шт.");
            Console.WriteLine($"Новая общая стоимость: {laptop.GetTotalPrice():C}");

            // Вывод списка товаров магазина
            techStore.ListProducts();
        }
    }
}
