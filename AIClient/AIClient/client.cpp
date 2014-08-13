#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);

		tcp::resolver::query query("localhost", "1337");

		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		std::string message = "Test";
		boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(message),
						   boost::asio::transfer_all(), ignored_error);

		for (;;)
		{
			//Buffer used to catch the message
			boost::array<char, 128> buf;
			boost::system::error_code error;

			//we read the buffer to put the message in the buffer
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			//We show what's in the buffer
			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}