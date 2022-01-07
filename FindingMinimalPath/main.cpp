#include "Matrix.h"
#include <string>


void print_pathes(const Matrix& vertex_matrix, const Matrix& length_matrix)
{
	bool print_all_pathes = false;
	char vertex_start = 'A';
	int16_t need_transit_size = -1;
	int16_t n = vertex_matrix.get_number_of_vertex();

	char choice = ' ';
	while (choice != 'y' && choice != 'n')
	{
		std::cout << "Print all transit pathes? (y/n): ";
		std::cin >> choice;
	}

	if (choice == 'y')
	{
		print_all_pathes = true;
	}
	else
	{
		std::cout << "Enter the initial vertex to build the tree: ";
		std::cin >> vertex_start;
		
		if (vertex_start > 'A' + n - 1 || vertex_start < 'A')
		{
			std::cout << "Incorrect vertex!" << std::endl;
			return;
		}

		std::cout << "Enter the minimal transit size (Enter -1 to print all): ";
		std::cin >> need_transit_size;

		if (need_transit_size > n - 1 || need_transit_size < -1)
		{
			std::cout << "Incorrect transit size!" << std::endl;
			return;
		}
	}

	uint16_t start = static_cast<uint16_t>(vertex_start - 'A');
	uint16_t end = 0;
	std::string path;

	if (print_all_pathes)
	{
		std::cout << "The shortest transit routes:" << std::endl;
	}
	else
	{
		std::cout << "The shortest " << ((need_transit_size == -1) ? "" : (std::to_string(need_transit_size) + '-')) 
			<< "transit routes from the vertex " << vertex_start << ":" << std::endl;
	}


	for (int16_t i = start; i < n; ++i, ++start)
	{
		for (int16_t j = 0; j < n; ++j, ++end)
		{
			path = "";
			uint16_t next_point = vertex_matrix.at(start, end);

			path += 'A' + static_cast<char>(start);
			while (next_point != INF)
			{
				path += static_cast<char>(next_point);
				if (vertex_matrix.at(next_point, end) == end + 'A')
					break;
				next_point = vertex_matrix.at(next_point - 'A', end);
			}

			if ((path.length() - 1) == need_transit_size || need_transit_size == -1)
				std::cout << path << "[" << length_matrix.at(start, end) << "]" << std::endl;
		}
		end = 0;
		
		if (!print_all_pathes)
			break;
	}
}


Matrix matrix_method(const Matrix& mat)
{
	Matrix dist(mat);

	std::cout << std::endl;

	int16_t n = mat.get_number_of_vertex();
	for (int16_t i = 0; i < n - 1; ++i)
	{
		std::cout << "Interation " << (i + 1) << ":\n" << dist << std::endl;
		dist.multiply(mat, MATRIX_METHOD);
	}

	return dist;
}

void floyd_method(const Matrix& dist, const Matrix& mat)
{
	Matrix g(mat);
	
	int16_t n = g.get_number_of_vertex();
	for (int16_t i = 0, j = 0; i < n; ++i, ++j)
	{
		g.at(i, j) = INF;
	}

	std::cout << "\n\nG matrix:\n" << g << std::endl;
	g.multiply(dist, FLOYD_METHOD);
	std::cout << "\n\nPath matrix:\n";
	g.print_points();

	std::cout << std::endl;
	print_pathes(g, dist);
}

int main()
{
	int16_t n = 0;

	std::cout << "Enter number of vertex: ";
	std::cin >> n;

	Matrix mat(n, n);
	std::cout << "Enter matrix [-1 == Inf]:" << std::endl;
	std::cin >> mat;

	std::cout << "\n\nMatrix method:" << std::endl;
	Matrix dist(matrix_method(mat));
	std::cout << "Floyd method:" << std::endl;
	floyd_method(dist, mat);

	return 0;
}