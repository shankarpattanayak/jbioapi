/* JBioAPI: a library of tools for accessing BioAPI-compliant biometric
 * service providers in Java.
 * 
 * Copyright (C) 2005 Michael R. Crusoe <michael@qrivy.net>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
package net.qrivy.jbioapi;

import java.util.HashMap;
import java.util.Map;

import net.qrivy.bioapi.BioAPIConstants;

/**
 * A Java Exception corresponding to an error received from the BioAPI framework.
 * 
 * @author Michael R. Crusoe <michael@qrivy.net>
 *
 */
public class BioApiException extends Exception {

	private static Map errorCodes = new HashMap(1);

	// TODO: Obviously need fleshing out
	static {
		errorCodes
				.put(
						Long
								.valueOf((long) BioAPIConstants.BioAPI_ERRCODE_INCOMPATIBLE_VERSION),
						"The given version is not compatible with the current version");
		errorCodes.put(Long
				.valueOf((long) BioAPIConstants.BioAPI_ERRCODE_INVALID_DATA),
				"Invalid Data.");

	}

	private long errorCode;

	/**
	 * Creates a new BioApiException based upon the given error code
	 * 
	 * @param _errorCode As defined in the BioAPI 1.10 specification
	 * @see "bioapi_err.h"
	 */
	public BioApiException(long _errorCode) {
		super();
		errorCode = _errorCode;
	}

	public long getErrorCode() {
		return errorCode;
	}

	/**
	 * Provides an explanation, if any, of this Exception
	 * 
	 * @return A String describing this Exception, if any -- otherwise a null
	 */
	public String explain() {
		return explain(errorCode);
	}

	/**
	 * Provide an explanation, if any, of a given exception
	 * 
	 * @param code The error code to explain
	 * @return A String describing the given error code, if any -- otherwise a null
	 */
	public static String explain(long code) {
		return (String) errorCodes.get(Long.valueOf(code));
	}

}
