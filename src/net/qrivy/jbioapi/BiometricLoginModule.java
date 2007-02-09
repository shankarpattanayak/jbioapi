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

import java.io.IOException;
import java.util.Map;

import javax.security.auth.Subject;
import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.callback.NameCallback;
import javax.security.auth.callback.UnsupportedCallbackException;
import javax.security.auth.login.AccountNotFoundException;
import javax.security.auth.login.FailedLoginException;
import javax.security.auth.login.LoginException;

import net.qrivy.bioapi.BioAPI;
import net.qrivy.bioapi.BioAPI_BIR;
import net.qrivy.bioapi.verifyResult;

/**
 * A JAAS LoginModule that verifies the user via a BioAPI compliant BSP.
 * 
 * The BiometricLoginModule looks for the following JAAS authentication options:
 * 
 * <table>
 * <tr>
 * <td>bspUuid</td>
 * <td>The <b>required </b> UUID of the BiometricServiceProvider to use</td>
 * </tr>
 * <tr>
 * <td>deviceid</td>
 * <td>The ID number of the device, by default 0</td>
 * </tr>
 * <tr>
 * <td>storageDirectory</td>
 * <td>The directory to read the BIRs from, by default /etc/bioapi/birs</td>
 * </tr>
 * </table>
 * 
 * @author Michael R. Crusoe <michael@qrivy.net>
 */
public class BiometricLoginModule implements
		javax.security.auth.spi.LoginModule {

	private BiometricServiceProvider bsp;

	private CallbackHandler cbHandler;

	private boolean success = false;

	private Map sharedState;

	private Map options;

	/*
	 * Default Constructor
	 */
	public BiometricLoginModule() {
		super();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.security.auth.spi.LoginModule#initialize(javax.security.auth.Subject,
	 *      javax.security.auth.callback.CallbackHandler, java.util.Map,
	 *      java.util.Map)
	 */
	public void initialize(Subject subject, CallbackHandler _cbHandler,
			Map _sharedState, Map _options) {
		cbHandler = _cbHandler;
		sharedState = _sharedState;
		options = _options;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.security.auth.spi.LoginModule#login()
	 */
	public boolean login() throws LoginException {
		success = verify(getBir(getBirDirectory() + getUsername() + ".bir"));
		if (success) {
			return true;
		} else {
			throw new FailedLoginException("No biometric match.");
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.security.auth.spi.LoginModule#commit()
	 */
	public boolean commit() throws LoginException {
		return success;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.security.auth.spi.LoginModule#abort()
	 */
	public boolean abort() throws LoginException {
		return success;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.security.auth.spi.LoginModule#logout()
	 */
	public boolean logout() throws LoginException {
		return true;
	}

	private String getUsername() throws LoginException {
		if (sharedState.containsKey("javax.security.auth.login.name")) {
			return (String) sharedState.get("javax.security.auth.login.name");
		} else {
			try {
				if (cbHandler == null) {
					throw new LoginException("Needs CallbackHandler");
				}
				NameCallback nc = new NameCallback(
						"Enter username for biometric verification: ");
				cbHandler.handle(new Callback[] { nc });
				return nc.getName();
			} catch (IOException e1) {
				LoginException e = new AccountNotFoundException(
						"Could not get username");
				e.initCause(e1);
				throw e;
			} catch (UnsupportedCallbackException e1) {
				LoginException e = new AccountNotFoundException(
						"Could not get username");
				e.initCause(e1);
				throw e;
			}
		}
	}

	private long getDeviceID() {
		if (options.containsKey("deviceId")) {
			return Long.parseLong((String) options.get("deviceId"));
		} else {
			return 0;
		}

	}

	private String getBspUuid() throws LoginException {
		if (options.containsKey("bspUuid")) {
			return (String) options.get("bspUuid");
		} else {
			throw new LoginException("No configured BiometricServiceProvider");
		}
	}

	/**
	 * @return
	 */
	private String getBirDirectory() {
		if (options.containsKey("storageDirectory")) {
			return (String) options.get("storageDirectory");
		} else {
			return "/etc/bioapi/birs/";
		}
	}

	private boolean verify(BioAPI_BIR bir) throws LoginException {
		verifyResult result;
		try {
			bsp = BiometricsFramework.getBiometricServiceProvider(getBspUuid(),
					getDeviceID());
			result = bsp.verify(1, 0, true, bir, -1);
			bir.delete();
		} catch (Exception e1) {
			LoginException e = new LoginException();
			e.initCause(e1);
			throw e;
		}
		return (result.getResult() == BioAPI.BioAPI_FALSE) ? false : true;
	}

	private BioAPI_BIR getBir(String filename) throws LoginException {
		try {
			return BiometricsFramework.readBir(filename);
		} catch (IOException e1) {
			LoginException e = new AccountNotFoundException(
					"Could not read template from " + filename);
			e.initCause(e1);
			throw e;
		}
	}
}