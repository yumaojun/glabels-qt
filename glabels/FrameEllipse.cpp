/*  FrameEllipse.cpp
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FrameEllipse.h"

#include "Constants.h"
#include "StrUtil.h"


namespace glabels
{

	FrameEllipse::FrameEllipse( const Distance& w,
				    const Distance& h,
				    const Distance& waste,
				    const QString&  id )
		: mW(w), mH(h), mWaste(waste), Frame(id)
	{
		mPath.addEllipse( 0, 0, mW.pt(), mH.pt() );
		mClipPath.addEllipse( -mWaste.pt(), -mWaste.pt(), (mW+2*mWaste).pt(), (mH+2*mWaste).pt() );
	}

	FrameEllipse::FrameEllipse( const FrameEllipse& other )
		: mW(other.mW), mH(other.mH), mWaste(other.mWaste), mPath(other.mPath), Frame(other)
	{
		// empty
	}

	
	Frame* FrameEllipse::dup() const
	{
		return new FrameEllipse( *this );
	}


	Distance FrameEllipse::w() const
	{
		return mW;
	}

	
	Distance FrameEllipse::h() const
	{
		return mH;
	}
	

	Distance FrameEllipse::waste() const
	{
		return mWaste;
	}


	QString FrameEllipse::sizeDescription( const Units& units ) const
	{
		if ( units.toEnum() == Units::IN )
		{
			QString wStr = StrUtil::formatFraction( mW.in() );
			QString hStr = StrUtil::formatFraction( mH.in() );

			return QString().sprintf( "%s x %s %s",
						  qPrintable(wStr),
						  qPrintable(hStr),
						  qPrintable(units.toTrName()) );
		}
		else
		{
			return QString().sprintf( "%.5g x %.5g %s",
						  mW.inUnits(units),
						  mH.inUnits(units),
						  qPrintable(units.toTrName()) );
		}
	}


	bool FrameEllipse::isSimilarTo( Frame* other ) const
	{
		if ( FrameEllipse* otherEllipse = dynamic_cast<FrameEllipse*>(other) )
		{
			if ( (fabs( mW - otherEllipse->mW ) <= EPSILON) &&
			     (fabs( mH - otherEllipse->mH ) <= EPSILON) )
			{
				return true;
			}
		}
		return false;
	}


	const QPainterPath& FrameEllipse::path() const
	{
		return mPath;
	}

	
	const QPainterPath& FrameEllipse::clipPath() const
	{
		return mClipPath;
	}

	
	QPainterPath FrameEllipse::marginPath( const Distance& size ) const
	{
		Distance w = mW - 2*size;
		Distance h = mH - 2*size;

		QPainterPath path;
		path.addEllipse( size.pt(), size.pt(), w.pt(), h.pt() );

		return path;
	}

} // namespace glabels
