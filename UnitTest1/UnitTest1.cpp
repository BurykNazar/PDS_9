#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab_9\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestReadValidFile)
		{
			string path = "valid_graph.txt";
			ofstream outFile(path);
			outFile << "1 2\n2 3\n3\n";
			outFile.close();

			Assert::IsTrue(read(path));
			Assert::AreEqual(size_t(3), graph.size());
			Assert::AreEqual(size_t(2), graph[0].size());
			Assert::AreEqual(0U, graph[0][0]); 
		}
		TEST_METHOD(TestReadInvalidFile)
		{
			Assert::IsFalse(read("non_existent_file.txt"));
		}

		TEST_METHOD(TestBFS)
		{
			graph = { {1}, {0, 2}, {1} };
			bfsNumber.clear();
			bfsNumber.resize(graph.size(), -1);

			bfs(0, graph);

			Assert::AreEqual(1, bfsNumber[0]);
			Assert::AreEqual(2, bfsNumber[1]);
			Assert::AreEqual(3, bfsNumber[2]);
		}
	};
}
