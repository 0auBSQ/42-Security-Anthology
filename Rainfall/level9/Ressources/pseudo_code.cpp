class N
{
	public:
		static char s[108] = 0x8048848; // 0x6c, the number after is a litteral
		int n;
		N(unsigned int n);
		setAnnotation(char *s);
		operator+(N const& other);
		operator-(N const& other);
};

void N::N(unsigned int n) {
	this->n = (int)n;
}

void N::setAnnotation(char *s) {
	memcpy((N::s + 4), s, strlen(s));
}

int N::operator+(N const& other) {
	return (this->n + other.n);
}

int N::operator-(N const& other) {
	return (this->n - other.n);
}

int main(int argc, char **argv) {
	// The assembly actually compare it with 1, but we add the program name here
	if (argc < 2)
		exit(1);
	a = new N(5);
	b = new N(6);
	a->setAnnotation(argv[1]);
	return (a + b);
}