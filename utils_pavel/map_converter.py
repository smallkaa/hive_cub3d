import sys
import os

def get_map_from_file(filename):
    """
    Читает карту из .cub файла, корректно пропуская строки конфигурации
    и пустые строки перед картой.
    """
    with open(filename, 'r') as f:
        lines = f.readlines()

    map_lines = []
    in_map_section = False
    config_identifiers = ("NO", "SO", "WE", "EA", "F", "C")

    for line in lines:
        if in_map_section:
            map_lines.append(line.rstrip('\n'))
            continue

        stripped_line = line.strip()
        if not stripped_line:
            continue
        
        parts = stripped_line.split()
        if parts and parts[0] in config_identifiers:
            continue
        
        in_map_section = True
        map_lines.append(line.rstrip('\n'))

    while map_lines and not map_lines[-1].strip():
        map_lines.pop()
        
    return map_lines

def generate_c_code(map_lines, c_filename):
    """
    Генерирует C-файл с функцией инициализации карты в виде
    одного плоского массива (char *).
    """
    if not map_lines:
        print(f"Предупреждение: Карта в файле не найдена. Файл '{c_filename}' не будет создан.")
        return

    size_y = len(map_lines)
    size_x = max(len(line) for line in map_lines) if map_lines else 0

    # Создаем "плоское" представление карты для C-кода
    flat_map_chars = []
    for line in map_lines:
        processed_line = line.ljust(size_x, ' ') # Дополняем пробелами
        for char in processed_line:
            # Заменяем игрока на '0' и экранируем спецсимволы
            final_char = '0' if char in "NSEW" else char
            if final_char == '\\':
                flat_map_chars.append("'\\\\'")
            elif final_char == "'":
                flat_map_chars.append("'\\''")
            else:
                flat_map_chars.append(f"'{final_char}'")

    c_array_content = ",\n        ".join(", ".join(flat_map_chars[i:i+size_x]) for i in range(0, len(flat_map_chars), size_x))

    with open(c_filename, 'w') as f:
        f.write('#include <stdlib.h>\n')
        f.write('#include <string.h>\n\n')
        f.write('typedef struct s_map\n')
        f.write('{\n')
        f.write('    char        *area; // Карта как один массив\n')
        f.write('    int         size_x;\n')
        f.write('    int         size_y;\n')
        f.write('} t_map;\n\n')

        f.write('void init_map(t_map *map)\n')
        f.write('{\n')
        f.write(f'    const int width = {size_x};\n')
        f.write(f'    const int height = {size_y};\n\n')
        f.write('    // Статическое представление карты для копирования\n')
        f.write('    static const char static_map[width * height] = {\n')
        f.write(f'        {c_array_content}\n')
        f.write('    };\n\n')
        f.write('    map->size_x = width;\n')
        f.write('    map->size_y = height;\n')
        f.write('    map->area = (char *)malloc(sizeof(char) * width * height);\n')
        f.write('    if (!map->area)\n')
        f.write('        return;\n\n')
        f.write('    memcpy(map->area, static_map, width * height);\n')
        f.write('}\n')
    
    print(f"Файл '{c_filename}' успешно сгенерирован (упрощенная версия).")

def main():
    """Главная функция."""
    if len(sys.argv) != 2:
        print(f"Использование: python {sys.argv[0]} <path_to_map.cub>")
        sys.exit(1)

    cub_filename = sys.argv[1]
    if not os.path.exists(cub_filename):
        print(f"Ошибка: Файл '{cub_filename}' не найден.")
        sys.exit(1)

    map_lines = get_map_from_file(cub_filename)
    
    base_name = os.path.splitext(os.path.basename(cub_filename))[0]
    if not base_name:
        base_name = 'map'
    c_filename = f"{base_name}.c"
    
    generate_c_code(map_lines, c_filename)

if __name__ == '__main__':
    main()