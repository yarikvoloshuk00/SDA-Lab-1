class GraphApp:
    def __init__(self):
        # Внутреннее хранилище всегда в виде списка смежности
        # Формат: {вершина: [смежные_вершины]}
        self.adj_list = {}

    def input_adjacency_list(self):
        self.adj_list = {}
        n = int(input("Введите количество вершин: "))
        print("Вводите смежные вершины через пробел (если их нет, нажмите Enter):")
        for i in range(1, n + 1):
            neighbors = input(f"Вершина {i}: ").strip().split()
            self.adj_list[i] = [int(x) for x in neighbors]
        print("Граф успешно сохранен!")

    def input_adjacency_matrix(self):
        self.adj_list = {}
        n = int(input("Введите размерность матрицы (количество вершин): "))
        print(f"Введите {n} строк(и) матрицы (числа через пробел):")
        for i in range(1, n + 1):
            row = list(map(int, input(f"Строка {i}: ").strip().split()))
            self.adj_list[i] = []
            for j in range(len(row)):
                if row[j] == 1:
                    self.adj_list[i].append(j + 1)
        print("Матрица преобразована и сохранена как список смежности!")

    def input_incidence_matrix(self):
        self.adj_list = {}
        edges_count = int(input("Введите количество ребер (строк): "))
        tops_count = int(input("Введите количество вершин (столбцов): "))
        
        # Инициализируем пустой список смежности
        for i in range(1, tops_count + 1):
            self.adj_list[i] = []

        print(f"Введите {edges_count} строк(и) матрицы (числа через пробел):")
        for _ in range(edges_count):
            row = list(map(int, input().strip().split()))
            connected_nodes = [j + 1 for j in range(tops_count) if row[j] == 1]
            if len(connected_nodes) == 2:
                u, v = connected_nodes
                if v not in self.adj_list[u]: self.adj_list[u].append(v)
                if u not in self.adj_list[v]: self.adj_list[v].append(u)
        print("Матрица инцидентности преобразована и сохранена!")

    def print_adjacency_list(self):
        print("\n--- Список смежности ---")
        if not self.adj_list:
            print("Граф пуст.")
            return
        for node, neighbors in sorted(self.adj_list.items()):
            print(f"{node}: {', '.join(map(str, sorted(neighbors)))}")

    def print_adjacency_matrix(self):
        print("\n--- Матрица смежности ---")
        if not self.adj_list:
            print("Граф пуст.")
            return
        n = max(self.adj_list.keys()) if self.adj_list else 0
        for i in range(1, n + 1):
            row = []
            for j in range(1, n + 1):
                if j in self.adj_list.get(i, []):
                    row.append("1")
                else:
                    row.append("0")
            print(" ".join(row))

    def print_incidence_matrix(self):
        print("\n--- Матрица инцидентности ---")
        if not self.adj_list:
            print("Граф пуст.")
            return
        
        edges = []
        for u, neighbors in self.adj_list.items():
            for v in neighbors:
                if (v, u) not in edges and (u, v) not in edges:
                    edges.append((u, v))
        
        n = max(self.adj_list.keys()) if self.adj_list else 0
        for edge in edges:
            row = ["0"] * n
            row[edge[0] - 1] = "1"
            row[edge[1] - 1] = "1"
            print(" ".join(row))

    def run(self):
        while True:
            print("\n" + "="*30)
            print("1. Ввести Список смежности")
            print("2. Ввести Матрицу смежности")
            print("3. Ввести Матрицу инцидентности")
            print("4. Вывести Список смежности")
            print("5. Вывести Матрицу смежности")
            print("6. Вывести Матрицу инцидентности")
            print("0. Выход")
            
            choice = input("Выберите действие: ")
            
            if choice == '1': self.input_adjacency_list()
            elif choice == '2': self.input_adjacency_matrix()
            elif choice == '3': self.input_incidence_matrix()
            elif choice == '4': self.print_adjacency_list()
            elif choice == '5': self.print_adjacency_matrix()
            elif choice == '6': self.print_incidence_matrix()
            elif choice == '0': break
            else: print("Неверный ввод, попробуйте снова.")

if __name__ == "__main__":
    app = GraphApp()
    app.run()