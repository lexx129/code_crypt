import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;

/**
 * Created with IntelliJ IDEA.
 * User: admin
 * Date: 19.11.15
 * Time: 10:22
 * To change this template use File | Settings | File Templates.
 */
public class Main {
    public static void main(String[] args) throws IOException {
        RandomAccessFile f = new RandomAccessFile("C:\\Users\\admin\\Documents\\Visual Studio 2010\\Projects\\code_crypt\\Release\\code_crypt.exe", "rw");
        f.seek(1024);
        byte b[] = new byte[48];
        f.read(b, 0, 48);
        byte inc = 0x5A;
        for (int i = 0; i < b.length; i++) {
            b[i] = (byte) (b[i] ^ inc);
        }
        f.seek(1024);
        f.write(b);
        f.close();
    }
}
