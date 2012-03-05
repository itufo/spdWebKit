#include "config.h"
#include "Gradient.h"

#include "GraphicsContext.h"

namespace WebCore {

void Gradient::platformDestroy()
{
}

const Vector<Gradient::ColorStop, 2>& Gradient::getStops() const
{
    if (!m_stopsSorted) {
        if (m_stops.size())
            std::stable_sort(m_stops.begin(), m_stops.end(), compareStops);
        m_stopsSorted = true;
    }
    return m_stops;
}

void Gradient::fill(GraphicsContext* c, const FloatRect& r)
{
    c->fillRect(r, this);
}

} // namespace WebCore
