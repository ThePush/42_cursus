#include "Span.hpp"

Span::Span(const unsigned int& N)
    : m_size(N) { }

Span::Span(const Span& src)
    : m_spanvec(src.m_spanvec)
    , m_size(src.m_size) { }

Span::~Span() { }

Span& Span::operator=(const Span& rhs) {
    if (this != &rhs) {
        this->m_spanvec = rhs.m_spanvec;
        this->m_size = rhs.m_size;
    }

    return *this;
}

void Span::addNumber(const unsigned int& number) {
    if (m_spanvec.size() == this->m_size)
        throw std::length_error(" addNumber(): Vector full");

    m_spanvec.push_back(number);
}

/**
 * `addNumber()` takes a vector of integers and adds them to the `m_spanvec` vector
 * 
 * @param begin The beginning of the range to copy from.
 * @param end iterator to the element that follows the last element to be copied.
 */
void Span::addNumber(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end) {
    std::vector<int> check_source_vector_size = std::vector<int>(begin, end);
    if (check_source_vector_size.size() + m_spanvec.size() > m_size)
        throw std::length_error(" addNumber(): Source vector size is too big or target vector is full");

    m_spanvec.insert(m_spanvec.end(), begin, end);
}

void Span::printVector(void) const {
    std::cout << " printVector():" << std::endl;
    for (std::vector<int>::const_iterator i(m_spanvec.begin()); i != m_spanvec.end(); ++i)
        std::cout << " " << *i << std::endl;
}

/**
 * It sorts the vector, then iterates through it, comparing each element to the next one, and returns
 * the smallest difference
 * 
 * @return The smallest difference between two numbers in the vector.
 */
size_t Span::shortestSpan(void) {
    if (m_spanvec.size() < 2)
        throw std::logic_error("shortestSpan(): Not enough datas in vector");

    std::sort(m_spanvec.begin(), m_spanvec.end());
    size_t ret = std::abs(m_spanvec[0] - m_spanvec[1]);
    for (size_t i(0); i != m_spanvec.size() - 1; ++i) {
        if (m_spanvec[i + 1] - m_spanvec[i] < static_cast<int>(ret))
            ret = m_spanvec[i + 1] - m_spanvec[i];
    }
    return ret;
}

/**
 * It returns the longest span of the vector.
 * 
 * @return The difference between the largest and smallest element in the vector.
 */
size_t Span::longestSpan(void) {
    if (m_spanvec.size() < 2)
        throw std::logic_error("longestSpan(): Not enough datas in vector");
    return *max_element(m_spanvec.begin(), m_spanvec.end()) - *min_element(m_spanvec.begin(), m_spanvec.end());
}