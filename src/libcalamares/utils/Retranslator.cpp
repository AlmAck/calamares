/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Retranslator.h"

#include <QEvent>


namespace CalamaresUtils {


Retranslator::Retranslator( QObject* parent,
                            std::function< void ( void ) > retranslateFunc )
    : QObject( parent )
    , m_retranslateFunc( retranslateFunc )
{
    m_retranslateFunc();

    parent->installEventFilter( this );
}


bool
Retranslator::eventFilter( QObject* obj, QEvent* e )
{
    if ( obj == parent() )
    {
        if ( e->type() == QEvent::LanguageChange )
        {
            m_retranslateFunc();
            return true;
        }
    }
    // pass the event on to the base
    return QObject::eventFilter( obj, e );
}


} // namespace CalamaresUtils
