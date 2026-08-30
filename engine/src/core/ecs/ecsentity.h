namespace FikaECS
{
	class Entity
	{
	private:
		unsigned int id = 0;

	public:
		Entity() {}
		~Entity() {}

		void setId(unsigned int id);
		unsigned int getId() const { return id; }
	};
}