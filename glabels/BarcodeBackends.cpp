/*  BarcodeBackends.cpp
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
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

#include "BarcodeBackends.h"

#include "glbarcode/Factory.h"

#include "BarcodeBackends/GnuBarcode.h"
#include "BarcodeBackends/QrEncode.h"


namespace glabels
{
	
	//
	// Static data
	//
	QStringList BarcodeBackends::mBackendIdList;
	QMap<QString,QString> BarcodeBackends::mBackendNameMap;

	QList<BarcodeStyle> BarcodeBackends::mStyleList;
	

	BarcodeBackends::BarcodeBackends()
	{
		registerStyle( "code39", "", tr("Code 39"),
		               true, true, true, true, "1234567890", true, 10 );

		registerStyle( "code39ext", "", tr("Code 39 Extended"),
		               true, true, true, true, "1234567890", true, 10 );

		registerStyle( "upc-a", "", tr("UPC-A"),
		               true, false, true, false, "12345678901", false, 11 );

		registerStyle( "ean-13", "", tr("EAN-13"),
		               true, false, true, false, "123456789012", false, 12 );

		registerStyle( "postnet", "", tr("POSTNET (any)"),
		               false, false, true, false, "12345-6789-12", false, 11 );

		registerStyle( "postnet-5", "", tr("POSTNET-5 (ZIP only)"),
		               false, false, true, false, "12345", false, 5 );

		registerStyle( "postnet-9", "", tr("POSTNET-9 (ZIP+4)"),
		               false, false, true, false, "12345-6789", false, 9 );

		registerStyle( "postnet-11", "", tr("POSTNET-11 (DPBC)"),
		               false, false, true, false, "12345-6789-12", false, 11 );

		registerStyle( "cepnet", "", tr("CEPNET"),
		               false, false, true, false, "12345-678", false, 8 );

		registerStyle( "onecode", "", tr("USPS Intelligent Mail"),
		               false, false, true, false, "12345678901234567890", false, 20 );

		registerStyle( "datamatrix", "", tr("IEC16022 (DataMatrix)"),
		               false, false, true, false, "1234567890AB", false, 12 );

#if HAVE_GNU_BARCODE
		//
		// Libqrencode backend
		//
		registerBackend( "gnu-barcode", "GNU Barcode" );
		
		glbarcode::Factory::registerType( "gnu-barcode::ean",      GnuBarcode::Ean::create );
		glbarcode::Factory::registerType( "gnu-barcode::ean-8",    GnuBarcode::Ean8::create );
		glbarcode::Factory::registerType( "gnu-barcode::ean-8+2",  GnuBarcode::Ean8_2::create );
		glbarcode::Factory::registerType( "gnu-barcode::ean-8+5",  GnuBarcode::Ean8_5::create );
		glbarcode::Factory::registerType( "gnu-barcode::ean-13",   GnuBarcode::Ean13::create );
		glbarcode::Factory::registerType( "gnu-barcode::ean-13+2", GnuBarcode::Ean13_2::create );
		glbarcode::Factory::registerType( "gnu-barcode::ean-13+5", GnuBarcode::Ean13_5::create );

		registerStyle( "ean", "gnu-barcode", tr("EAN (any)"),
		               true, true, true, false, "000000000000 00000", false, 17 );
		registerStyle( "ean-8", "gnu-barcode", tr("EAN-8"),
		               true, true, true, false, "0000000", false, 7 );
		registerStyle( "ean-8+2", "gnu-barcode", tr("EAN-8+2"),
		               true, true, true, false, "0000000 00", false, 9 );
		registerStyle( "ean-8+5", "gnu-barcode", tr("EAN-8+5"),
		               true, true, true, false, "0000000 00000", false, 12 );
		registerStyle( "ean-13", "gnu-barcode", tr("EAN-13"),
		               true, true, true, false, "000000000000", false, 12 );
		registerStyle( "ean-13+2", "gnu-barcode", tr("EAN-13+2"),
		               true, true, true, false, "000000000000 00", false, 14 );
		registerStyle( "ean-13+5", "gnu-barcode", tr("EAN-13+5"),
		               true, true, true, false, "000000000000 00000", false, 17 );
#endif // HAVE_GNU_BARCODE

#if HAVE_QRENCODE
		//
		// Libqrencode backend
		//
		registerBackend( "qrencode", "QREncode" );
		
		glbarcode::Factory::registerType( "qrencode::qrcode", QrEncode::QrCode::create );

		registerStyle( "qrcode", "qrencode", tr("IEC18004 (QRCode)"),
		               false, false, true, false, "1234567890AB", false, 12 );
#endif // HAVE_QRENCODE

	}


	void BarcodeBackends::init()
	{
		static BarcodeBackends* singletonInstance = nullptr;
                
		if ( singletonInstance == nullptr )
		{
			singletonInstance = new BarcodeBackends();
		}
	}


	const QStringList& BarcodeBackends::backendList()
	{
		return mBackendIdList;
	}

	
	QString BarcodeBackends::backendName( const QString& backendId )
	{
		return mBackendNameMap[ backendId ];
	}

	
	const QList<BarcodeStyle>& BarcodeBackends::styleList()
	{
		return mStyleList;
	}


	const BarcodeStyle& BarcodeBackends::defaultStyle()
	{
		return mStyleList[0];
	}


	const BarcodeStyle& BarcodeBackends::style( const QString& backendId, const QString& StyleId )
	{
		foreach ( const BarcodeStyle& bcStyle, mStyleList )
		{
			if ( (bcStyle.backendId() == backendId) && (bcStyle.id() == StyleId) )
			{
				return bcStyle;
			}
		}

		return defaultStyle();
	}


	void BarcodeBackends::registerBackend( const QString& backendId, const QString& backendName )
	{
		mBackendIdList.append( backendId );
		mBackendNameMap[ backendId ] = backendName;
	}


	void BarcodeBackends::registerStyle( const QString& id,
	                                     const QString& backendId,
	                                     const QString& name,
	                                     bool           canText,
	                                     bool           textOptional,
	                                     bool           canChecksum,
	                                     bool           checksumOptional,
	                                     const QString& defaultDigits,
	                                     bool           canFreeForm,
	                                     int            preferedN )
	{
		BarcodeStyle style( id, backendId, name,
		                    canText, textOptional,
		                    canChecksum, checksumOptional,
		                    defaultDigits,
		                    canFreeForm, preferedN );

		mStyleList.append( style );
	}

} // namespace glabels
