#include "Matrix.h"
#include <string>

#define N 6
#define TRANSIT_ROUTES -1

void print_pathes(const Matrix& vertex_matrix, const Matrix& length_matrix, int16_t need_path_size, char vertex_start = 'A')
{
	if (need_path_size > N - 1)
	{
		std::cout << "Incorrect path size!" << std::endl;
		return;
	}

	uint16_t start = static_cast<uint16_t>(vertex_start - 'A');
	uint16_t end = 0;
	std::string path;

	std::cout << "The Shortest "<< ((need_path_size == -1) ? "" : (std::to_string(need_path_size)+'-')) << "trinsit routes:" << std::endl;

	for (int16_t i = start; i < N; ++i, ++start)
	{
		for (int16_t j = 0; j < N; ++j, ++end)
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

			if (path.length() == need_path_size || need_path_size == -1)
				std::cout << path << "[" << length_matrix.at(start, end) << "]" << std::endl;
		}
		end = 0;
	}
}


Matrix matrix_method(const Matrix& mat)
{
	Matrix dist(mat);

	std::cout << std::endl;

	for (int16_t i = 0; i < N - 1; ++i)
	{
		std::cout << "Interation " << (i + 1) << ":\n" << dist << std::endl;
		dist.multiply(mat, MATRIX_METHOD);
	}

	return dist;
}

void floyd_method(const Matrix& dist, const Matrix& mat)
{
	Matrix g(mat);

	for (int16_t i = 0, j = 0; i < N; ++i, ++j)
	{
		g.at(i, j) = INF;
	}

	std::cout << "\n\nG matrix:\n" << g << std::endl;
	g.multiply(dist, FLOYD_METHOD);
	std::cout << "\n\nPath matrix:\n";
	g.print_points();

	std::cout << std::endl;
	print_pathes(g, dist, TRANSIT_ROUTES, 'F');
}

int main()
{
	Matrix mat(N, N);
	std::cout << "Enter matrix [-1 == Inf]:" << std::endl;
	std::cin >> mat;

	std::cout << "\n\nMatrix method:" << std::endl;
	Matrix dist(matrix_method(mat));
	std::cout << "Floyd method:" << std::endl;
	floyd_method(dist, mat);

	return 0;
}