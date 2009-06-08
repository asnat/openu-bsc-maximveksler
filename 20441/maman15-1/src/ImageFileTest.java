import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class ImageFileTest {
	char[][] asciiArtImage = { 
	 "ABC".toCharArray(),
     "DEF".toCharArray(),
     "OOO".toCharArray(),
     "123".toCharArray(),
     ",,,".toCharArray(),
     "PPP".toCharArray()
	};
	
	String asciiArtImageStr = 
		"ABC\n" 
		+ "DEF\n"
		+ "OOO\n"
		+ "123\n"
		+ ",,,\n"
		+ "PPP\n";
		
	String fileName = "asciiArt";

	ImageFile imageFile = new ImageFile(fileName, asciiArtImage);
	
	@Before
	public void setUp() throws Exception {
	}

	@Test
	public final void testOpen() {
		for(int i = 0; i < asciiArtImage.length; i++) {
			assertArrayEquals(asciiArtImage[i], ((char[][])imageFile.open())[i]);	
		}
		
		assertNotSame(asciiArtImage, imageFile.open());
	}

	@Test
	public final void testGetSize() {
		int asciiArtArraySize = 3*6;
		
		assertTrue(imageFile.getSize() == asciiArtArraySize);
	}

	@Test
	public final void testImageFile() {
		for(int i = 0; i < asciiArtImage.length; i++) {
			assertArrayEquals(((char[][]) imageFile.open())[i], asciiArtImage[i]);
		}
	}

	@Test
	public final void testToString() {
		assertTrue(asciiArtImageStr.equals(imageFile.toString()));
	}

	public final void testImageFileImageFile() {
		fail();
	}

}
