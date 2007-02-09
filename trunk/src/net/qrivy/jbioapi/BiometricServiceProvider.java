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

import net.qrivy.bioapi.BioAPI;
import net.qrivy.bioapi.BioAPI_BIR;
import net.qrivy.bioapi.SWIGTYPE_p_a_16__unsigned_char;
import net.qrivy.bioapi.verifyResult;

/**
 * @author Michael R. Crusoe <michael@qrivy.net
 * 
 */
public class BiometricServiceProvider {
	
	public final static short PURPOSE_ENROLL = 3;

	public final static short PURPOSE_ENROLL_FOR_VERIFICATION_ONLY = 4;

	public final static short PURRPOSE_ENROLL_FOR_IDENTIFICATION_ONLY = 5;

	private long handle;
	
	private SWIGTYPE_p_a_16__unsigned_char uuid;
	
	BiometricServiceProvider(long _handle, SWIGTYPE_p_a_16__unsigned_char _uuid) {
		handle = _handle;
		uuid = _uuid;
	}

	public BioAPI_BIR enroll(short purpose) throws BioApiException {
		return enroll(purpose, -1);
	}
	
	public BioAPI_BIR enroll(short purpose, int timeout) throws BioApiException {
		checkHandle();
		int birHandle = BioAPI.enroll(handle, purpose, timeout);
		return BioAPI.getBirFromHandle(handle, birHandle);
	}
	
	public verifyResult verify(int far, int frr, boolean preferFar, BioAPI_BIR bir, int timeout) throws BioApiException {
		long farOrFrr = (preferFar) ? BioAPI.BioAPI_FALSE : 1;
		return BioAPI.verifyBir(handle, far, frr, farOrFrr, bir, timeout);
	}

	private void checkHandle() {
		if (handle == 0) {
			throw new IllegalArgumentException("Stale Handle");
		}
	}

	public void destroy() {
		if (handle == 0) {
			return;
		}
		try {
			BioAPI.detachModule(handle);
			BioAPI.unloadModule(uuid);
		} catch (BioApiException e) {
		}
		handle = 0;
	}
	
	 protected void finalize() {
	 	destroy();
	 }
}