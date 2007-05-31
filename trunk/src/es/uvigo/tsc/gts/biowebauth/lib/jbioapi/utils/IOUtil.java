/* BioWebAuth (Biometrics for Web Authentication) is an open-source Java 
 * framework intended to provide web authentication based on BioAPI-compliant 
 * biometric software or devices.
 * 
 * Copyright (c) 2005-2007 Elisardo Gonzalez Agulla <eli@gts.tsc.uvigo.es> 
 *  		          & Enrique Otero Muras <eotero@gts.tsc.uvigo.es>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

package es.uvigo.tsc.gts.biowebauth.lib.jbioapi.utils;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public final class IOUtil {
    private static final int BUFFER_SIZE = 1024 * 4;
    
    public static void streamAndClose(InputStream in, OutputStream out) throws IOException {
        try {
            stream(in, out);
        } finally {
            try {
                in.close();
            } finally {
                out.close();
            }
        }
    }
    
    public static void stream(InputStream in, OutputStream out) throws IOException {
        // Copy the input stream to the output stream
        byte buffer[] = new byte[BUFFER_SIZE];
        int len = buffer.length;
        while (true) {
            len = in.read(buffer);
            if (len == -1) {
                break;
            }
            out.write(buffer, 0, len);
        }
        out.flush();
        
    }
}