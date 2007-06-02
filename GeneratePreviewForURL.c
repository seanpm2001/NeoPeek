/**
 * @file GeneratePreviewForURL.c
 *
 * Output hi-res preview image for a particular document type, if available.
 *
 *  $RCSfile$
 *
 *  $Revision$
 *
 *  last change: $Author$ $Date$
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU General Public License Version 2.1
 *
 *  Edward Peterlin, 2005
 *
 *  GNU Lesser Public License Version 2.1
 *  =============================================
 *  Copyright 2005 by Edward Peterlin (OPENSTEP@neooffice.org)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 ************************************************************************/

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>
#include "common.h"

/* -----------------------------------------------------------------------------
   Generate a preview for file

   This function's job is to create preview for designated file
   ----------------------------------------------------------------------------- */

OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options)
{	
	if(CFStringCompare(contentTypeUTI, CFSTR("org.oasis.opendocument.text"), 0)==kCFCompareEqualTo)
	{
		CGImageRef odPreviewImage=GetPreviewImageForOD(url);
		if(odPreviewImage)
		{
			CGContextRef drawRef=QLPreviewRequestCreateContext(preview, CGSizeMake(CGImageGetWidth(odPreviewImage), CGImageGetHeight(odPreviewImage)), 1, NULL);
			if(drawRef)
			{
				CGRect destRect;
				destRect.origin.x=destRect.origin.y=0;
				destRect.size=CGSizeMake(CGImageGetWidth(odPreviewImage), CGImageGetHeight(odPreviewImage));
				CGContextDrawImage(drawRef, destRect, odPreviewImage);
				
				CFRelease(drawRef);
			}
			CFRelease(odPreviewImage);
		}
	}
	
	return noErr;
}

void CancelPreviewGeneration(void* thisInterface, QLPreviewRequestRef preview)
{
    // implement only if supported
}
