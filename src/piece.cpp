#include <stdexcept>

#include "piece.h"

static const QChar TYPES_FLAVORS[][Piece::NB_FLAVORS] = {
    // standard
    { u'王',    0 , u'玉'},
    { u'飛', u'龍',    0 },
    { u'角', u'馬',    0 },
    { u'金',    0 ,    0 },
    { u'銀', u'全',    0 },
    { u'桂', u'圭',    0 },
    { u'香', u'杏',    0 },
    { u'歩', u'と',    0 },

    // Wa
    { u'鷲',    0 ,    0 },
    { u'狐',    0 ,    0 },
    { u'鷹', u'鶏',    0 },
    { u'兎', u'狐',    0 },
    { u'狼', u'熊',    0 },
    { u'鹿', u'猪',    0 },
    { u'犬', u'狼',    0 },
    { u'猿', u'鹿',    0 },
    { u'鳫', u'羽',    0 },
    { u'鶏', u'延',    0 },
    { u'羽', u'行',    0 },
    { u'烏', u'鷹',    0 },
    { u'鴟', u'鷲',    0 },
    { u'風', u'天',    0 },
    { u'車', u'牛',    0 },

    // Okisaki
    { u'妃',     0,    0 },
    { u'跳', u'今',    0 },
    { u'反', u'仝',    0 },
};

static const unsigned int NB_TYPES = sizeof(TYPES_FLAVORS) /
                                     sizeof(TYPES_FLAVORS[0]);

static const QChar SENTE_PREFIX = u' ';
static const QChar GOTE_PREFIX = u'v';

Piece::Piece(const Player player, const QChar type, const Flavor flavor) {
    if (player < NB_PLAYERS)
        mPlayer = player;
    else
        throw std::invalid_argument("Unknown player");

    if (flavor < NB_FLAVORS)
        mFlavor = flavor;
    else
        throw std::invalid_argument("Unknown piece flavor");

    mTypeIndex = Piece::typeIndex(type);
    if (TYPES_FLAVORS[mTypeIndex][flavor] == 0)
        throw std::invalid_argument("Piece type and flavor don't match");
}

QChar Piece::type() const
{
    return TYPES_FLAVORS[mTypeIndex][DEFAULT];
}

QChar Piece::kanji() const
{
    return TYPES_FLAVORS[mTypeIndex][mFlavor];
}

Piece *Piece::loadBOD(QTextStream &stream)
{
    QString buffer = stream.read(2);
    if (buffer.size() < 2)
        throw std::runtime_error("Incomplete piece");

    Player player = (buffer[0] == GOTE_PREFIX ? GOTE : SENTE);

    // XXX: use lookup table?
    for (unsigned int typeIndex = 0; typeIndex < NB_TYPES; typeIndex++)
        for (int flavor = 0; flavor < NB_FLAVORS; flavor++)
            if (buffer[1] == TYPES_FLAVORS[typeIndex][flavor])
                return new Piece(player, TYPES_FLAVORS[typeIndex][DEFAULT],
                                         static_cast<Flavor>(flavor));

    return nullptr;
}

void Piece::saveBOD(QTextStream &stream) const
{
    stream << (mPlayer == SENTE ? SENTE_PREFIX : GOTE_PREFIX) << kanji();
}

unsigned int Piece::typeIndex(const QChar type)
{
    for (unsigned int typeIndex = 0; typeIndex < NB_TYPES; typeIndex++)
        if (TYPES_FLAVORS[typeIndex][DEFAULT] == type)
            return typeIndex;

    throw std::invalid_argument("Unknown piece type");
}
