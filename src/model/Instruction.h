/*
 * model/Instruction.h is part of Brewtarget, and is Copyright the following
 * authors 2009-2021
 * - Jeff Bailey <skydvr38@verizon.net>
 * - Matt Young <mfsy@yahoo.com>
 * - Mik Firestone <mikfire@gmail.com>
 * - Philip Greggory Lee <rocketman768@gmail.com>
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MODEL_INSTRUCTION_H
#define MODEL_INSTRUCTION_H

// This class is completely outside the BeerXML spec.

#include <QDomNode>
#include <QString>
#include <QVector>

#include "model/NamedEntity.h"
#include "model/Recipe.h"
#include "TableSchema.h"

namespace PropertyNames::Instruction { static char const * const interval = "interval"; /* previously kpropInterval */ }
namespace PropertyNames::Instruction { static char const * const completed = "completed"; /* previously kpropCompleted */ }
namespace PropertyNames::Instruction { static char const * const timerValue = "timerValue"; /* previously kpropTimerValue */ }
namespace PropertyNames::Instruction { static char const * const hasTimer = "hasTimer"; /* previously kpropHasTimer */ }
namespace PropertyNames::Instruction { static char const * const directions = "directions"; /* previously kpropDirections */ }

/*!
 * \class Instruction
 *
 * \brief Model class for an instruction record in the database.
 */
class Instruction : public NamedEntity
{
   Q_OBJECT
   Q_CLASSINFO("signal", "instructions")
   friend class Database;
   friend class BeerXML;

public:

   Instruction( QString name, bool cache = true );
   virtual ~Instruction() {}

   Q_PROPERTY( QString directions READ directions WRITE setDirections /*NOTIFY changed*/ /*changedDirections*/ )
   Q_PROPERTY( bool hasTimer READ hasTimer WRITE setHasTimer /*NOTIFY changed*/ /*changedHasTimer*/ )
   Q_PROPERTY( QString timerValue READ timerValue WRITE setTimerValue /*NOTIFY changed*/ /*changedTimerValue*/ )
   Q_PROPERTY( bool completed READ completed WRITE setCompleted /*NOTIFY changed*/ /*changedCompleted*/ )
   Q_PROPERTY( double interval READ interval WRITE setInterval /*NOTIFY changed*/ /*changedInterval*/ )
   Q_PROPERTY( QList<QString> reagents READ reagents /*WRITE*/ /*NOTIFY changed*/ /*changedReagents*/ )

   Q_PROPERTY( int instructionNumber READ instructionNumber /*WRITE*/ /*NOTIFY changed*/ STORED false )

   // "set" methods.
   void setDirections(const QString& dir);
   void setHasTimer(bool has);
   void setTimerValue(const QString& timerVal);
   void setCompleted(bool comp);
   void setInterval(double interval);
   void addReagent(const QString& reagent);
   void setRecipe(Recipe * const recipe);

   // "get" methods.
   QString directions();
   bool hasTimer();
   QString timerValue();
   bool completed();
   //! This is a non-stored temporary in-memory set.
   QList<QString> reagents();
   double interval();

   int instructionNumber() const;

   static QString classNameStr();

   // Instruction objects do not have parents
   NamedEntity * getParent() { return nullptr; }
   virtual int insertInDatabase();
   virtual void removeFromDatabase();

signals:

protected:
   virtual bool isEqualTo(NamedEntity const & other) const;

private:
   Instruction(TableSchema* table, QSqlRecord rec,int t_key = -1);
   Instruction( Instruction const& other );

   QString m_directions;
   bool    m_hasTimer;
   QString m_timerValue;
   bool    m_completed;
   double  m_interval;
   Recipe * m_recipe;

   QList<QString> m_reagents;
};

Q_DECLARE_METATYPE( QList<Instruction*> )

//! \brief Compares Instruction pointers by Instruction::instructionNumber().
inline bool insPtrLtByNumber( Instruction* lhs, Instruction* rhs)
{
   return lhs->instructionNumber() < rhs->instructionNumber();
}

#endif
