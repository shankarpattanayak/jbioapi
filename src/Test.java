/* JBioAPI: a library of tools for accessing BioAPI-compliant biometric
 * service providers in Java.
 * 
 * Copyright (C) 2005 Michael R. Crusoe <michael@qrivy.net>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * JBioAPI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License in the file COPYING for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JBioAPI; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.callback.NameCallback;
import javax.security.auth.callback.UnsupportedCallbackException;
import javax.security.auth.login.LoginContext;
import javax.security.auth.login.LoginException;

import net.qrivy.bioapi.BioAPI_BIR;
import net.qrivy.jbioapi.BioApiException;
import net.qrivy.jbioapi.BiometricServiceProvider;
import net.qrivy.jbioapi.BiometricsFramework;

/**
 * JBioAPI Test Program -- demonstrates the {@link net.qrivy.jbioapi JBioAPI}
 * library by enrolling a user and verifying them using a JAAS
 * {@link net.qrivy.jbioapi.BiometricLoginModule BiometricLoginModule}
 * 
 * @author Michael R. Crusoe <michael@qrivy.net>
 * @see net.qrivy.jbioapi
 */
public class Test {

	/** The sample password BSP included with the reference implementation */
	private static final String defaultBspUuid = "{263a41e0-71eb-11d4-9c34-124037000000}";

	/**
	 * Main entry point.
	 * 
	 * @param args
	 *            The first argument could be the UUID of an alternative
	 *            BiometricServiceProvider
	 */
	public static void main(String[] args) {
		System.out.println("JBioAPI Test\n");

		if (System.getProperty("java.security.auth.login.config") == null) {
			if (new File("jbioapi.jaas.config").exists()) {
				System.setProperty("java.security.auth.login.config",
						"jbioapi.jaas.config");
				System.out
						.println("No \"java.security.auth.login.config\" property set, using default value of \"jbioapi.jaas.config");
			} else {
				System.out
						.println("No \"java.security.auth.login.config\" property set.");
			}
		}

		try {
			System.out.println("Part 1: Setup");
			System.out.println("Part 1: Number of installed BSPs: "
					+ BiometricsFramework.getNumberOfModules());
			BiometricServiceProvider pwBsp = BiometricsFramework
					.getBiometricServiceProvider(getBspUuid(args), 0);
			System.out.println("\nPart 2: Enrollment");
			BioAPI_BIR bir = pwBsp
					.enroll(BiometricServiceProvider.PURPOSE_ENROLL_FOR_VERIFICATION_ONLY);
			BiometricsFramework.writeBir(bir, "test.bir");
			bir.delete(); // Optional,
			bir = null; //           but recommended
			LoginContext lc;
			try {
				lc = new LoginContext("Test", new simpleCallbackHandler());
				System.out.println("\nPart 3: Verification using JAAS");
				System.out.println("(Enter the username \"test\")");
				lc.login();
				System.out
						.println("Part 3: Success! User verified using the BiometricLoginModule.");
			} catch (SecurityException se) {
				System.err
						.println("Part 3: Failure! Did you install a login configuration?");
				System.err
						.println("Set it using the java.security.auth.login.config property");
				System.err
						.println("You can do this via the command line by "
								+ "adding \"-Djava.security.auth.login.config=pathtojavaloginconfig\"");
				throw se;
			} catch (LoginException e1) {
				System.out.println("User not verified.");
				e1.printStackTrace();
			}
		} catch (BioApiException e2) {
			System.err.println("BioAPI Error: 0x"
					+ Long.toHexString(e2.getErrorCode()));
			System.err.println(e2.explain());
			e2.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		BiometricsFramework.terminate(); // Optional, but recommended
	}

	/**
	 * Returns the default UUID, or a user-specified UUID
	 * @return A UUID
	 */
	private static String getBspUuid(String[] args) {
		if (args.length > 0) {
			return args[0];
		} else {
			String bspUuid = defaultBspUuid;
			System.out
					.println("No BSP UUID specified on the command line, using "
							+ bspUuid + " instead.");
			return bspUuid;
		}

	}

	/**
	 * A CallbackHandler specially created to help demonstrate the
	 * BiometricLoginModule
	 * 
	 * Adapted from
	 * http://java.sun.com/j2se/1.5.0/docs/guide/security/jaas/tutorials/GeneralAcnOnly.html
	 * 
	 * @author Michael R. Crusoe
	 *  
	 */
	static class simpleCallbackHandler implements CallbackHandler {

		simpleCallbackHandler() {
			super();
		}

		/*
		 * (non-Javadoc)
		 * 
		 * @see javax.security.auth.callback.CallbackHandler#handle(javax.security.auth.callback.Callback[])
		 */
		public void handle(Callback[] callbacks) throws IOException,
				UnsupportedCallbackException {
			for (int index = 0; index < callbacks.length; index++) {
				if (callbacks[index] instanceof NameCallback) {
					// prompt the user for a username
					NameCallback nc = (NameCallback) callbacks[index];
					System.err.print(nc.getPrompt());
					System.err.flush();
					nc.setName((new BufferedReader(new InputStreamReader(
							System.in))).readLine());
				}
			}

		}

	}
}
