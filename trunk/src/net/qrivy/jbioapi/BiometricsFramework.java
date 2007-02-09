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

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import net.qrivy.bioapi.BioAPI;
import net.qrivy.bioapi.BioAPI_BIR;
import net.qrivy.bioapi.SWIGTYPE_p_a_16__unsigned_char;
import net.qrivy.bioapi.SchemaArray;

/**
 * @author Michael R. Crusoe <michael@qrivy.net>
 * 
 */
public class BiometricsFramework implements Runnable {

	static {
		Runtime.getRuntime().addShutdownHook(new Thread(new BiometricsFramework()));
		try {
			System.loadLibrary("jbioapi");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Could not load the jbioapi library ("
					+ System.mapLibraryName("jbioapi") + ") using the "
					+ "java.library.path property. Is the BioAPI library "
					+ "installed on the path? You can set this "
					+ "property by adding \"-Djava.library.path=path\" "
					+ "to the command line.");
						throw e;
		}
	}

	private static boolean dirty = true;

	private static BiometricsFramework instance;

	private static Map bsps;

	public static BiometricServiceProvider getBiometricServiceProvider(
			String uuid, long deviceID) throws BioApiException {
		setup();
		Long hash = Long.valueOf((long) uuid.hashCode() * deviceID);
		if (!bsps.containsKey(hash)) {
			SWIGTYPE_p_a_16__unsigned_char moduleUuid;
			long bspHandle;
			moduleUuid = BioAPI.getStructuredUuid(uuid);
			BioAPI.loadModule(moduleUuid);
			bspHandle = BioAPI.attachModule(moduleUuid, BioAPI
					.getBioAPIMemoryFuncs(), deviceID);
			bsps.put(hash, new BiometricServiceProvider(bspHandle, moduleUuid));
		}
		return (BiometricServiceProvider) bsps.get(hash);
	}

	public static long getNumberOfModules() throws BioApiException {
		setup();
		return BioAPI.getNumberOfModules();
	}

	public static SchemaArray getSchemas() throws BioApiException {
		return SchemaArray.frompointer(BioAPI.getSchemas());
	}

	public static BioAPI_BIR readBir(String filename) throws IOException {
		BioAPI_BIR bir;
		FileInputStream in = null;
		FileChannel channel = null;
		try {
			in = new FileInputStream(filename);
			channel = in.getChannel();
			long channelSize = channel.size();
			ByteBuffer buffer = ByteBuffer.allocateDirect(16);
			channel.read(buffer);
			bir = new BioAPI_BIR();
			BioAPI.setBirHeader(bir, buffer);
			buffer = ByteBuffer.allocateDirect((int) (channelSize - channel
					.position()));
			channel.read(buffer);
			BioAPI.setBirData(bir, buffer);
			if (channel.position() != channelSize) {
				buffer = buffer.compact();
				BioAPI.setSignatureData(bir, buffer);
			}
			channel.close();
			channel = null;
			in.close();
			in = null;
		} catch (IOException e1) {
			if (channel != null) {
				try {
					channel.close();
					channel = null;
				} catch (IOException e2) {
					channel = null;
				}
			}
			if (in != null) {
				try {
					in.close();
					in = null;
				} catch (IOException e2) {
					in = null;
				}
			}
			throw e1;
		}
		return bir;
	}

	public static void writeBir(BioAPI_BIR bir, String filename)
			throws IOException {
		FileOutputStream out = null;
		FileChannel channel = null;
		try {
			out = new FileOutputStream(filename);
			channel = out.getChannel();
			channel.write(BioAPI.getBirHeaderByteBuffer(bir));
			channel.write(BioAPI.getBirDataByteBuffer(bir));
			channel.write(BioAPI.getBirSignatureByteBuffer(bir));
			channel.close();
			channel = null;
			out.close();
			out = null;
		} catch (IOException e) {
			if (channel != null) {
				try {
					channel.close();
				} catch (IOException e1) {
				}
				channel = null;
			}
			if (out != null) {
				try {
					out.close();
				} catch (IOException e1) {
				}
				out = null;
			}
			IOException b = new IOException("Error writing BIR to " + filename);
			b.initCause(e);
			throw b;
		}
	}

	private static void init() throws BioApiException {
		BioAPI.init();
		dirty = false;
	}

	public static void terminate() {
		Iterator bspIterator = bsps.keySet().iterator();
		while (bspIterator.hasNext()) {
			((BiometricServiceProvider) (bsps.get((Long) bspIterator.next())))
					.destroy();
			bspIterator.remove();
		}
		if (!dirty) {
			try {
				BioAPI.terminate();
			} catch (BioApiException e) {
			}
			dirty = true;
		}
	}

	private static void setup() throws BioApiException {
		if (bsps == null) {
			bsps = new HashMap();
		}
		if (dirty) {
			init();
		}
	}

	protected void finalize() throws Throwable {
		super.finalize();
		terminate();
	}

	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		BiometricsFramework.terminate();
	}

}
