import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class DirectoryTest {

	char[][] chr1 = {{'a', 'b'}, {'c', 'd'}};
	ImageFile imageFile1 = new ImageFile("imageFile1", chr1);

	char[][] chr2 = {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};
	ImageFile imageFile2 = new ImageFile("imageFile2", chr2);

	TextFile textFile1 = new TextFile("textFile1", "AB");
	TextFile textFile2 = new TextFile("textFile2", "ABcd");
	
	// All files are listed flat.
	MyFile[] directory1 = {imageFile1, imageFile2, textFile1, textFile2};
	
	// imageFile2 removed.
	MyFile[] directory1_img2_removed = {imageFile1, textFile1, textFile2};

	// 0 files.
	MyFile[] directory2 = {};

	// 0 files.
	MyFile[] directory2__txt1__added = {textFile1};
	MyFile[] directory2__txt1_txt2__added = {textFile1, textFile2};
	 

	@Before
	public void setUp() throws Exception {
	}

	@Test
	public final void testOpen() {
		Directory tested; 

		{
		tested = new Directory("ABC");

		// Check we can add new files
		assertTrue(tested.addFile(textFile1));
		assertTrue(tested.addFile(textFile2));
		assertTrue(tested.addFile(imageFile1));

		MyFile[] files = (MyFile[])tested.open();

		assertNotSame(textFile1, files[0]);
		assertEquals(textFile1.open(), files[0].open());
		
		assertNotSame(textFile2, files[1]);
		assertEquals(textFile2.open(), files[1].open());
		
		assertNotSame(imageFile1, files[2]);
		assertEquals(imageFile1.getName(), files[2].getName());
		
		
		Directory directory_0 = new Directory("/");
		directory_0.addFile(textFile2);
		directory_0.addFile(imageFile1);
		
		assertTrue(tested.addFile(directory_0));
		assertTrue(tested.getSize() == 3);
		
		files = (MyFile[])tested.open();

		assertNotSame(textFile1, files[0]);
		assertEquals(textFile1.open(), files[0].open());
		
		assertNotSame(textFile2, files[1]);
		assertEquals(textFile2.open(), files[1].open());
		
		assertNotSame(imageFile1, files[2]);
		assertEquals(imageFile1.getName(), files[2].getName());

		}
	}

	@Test
	public final void testGetSize() {
		Directory tested; 

		{
		tested = new Directory("ABC");

		// Check we can add new files
		assertTrue(tested.addFile(textFile1));
		assertTrue(tested.addFile(textFile2));
		assertTrue(tested.addFile(imageFile1));

		assertTrue(tested.getSize() == 3); 

		Directory directory_0 = new Directory("/");
		directory_0.addFile(textFile2);
		directory_0.addFile(imageFile1);
		
		assertTrue(tested.addFile(directory_0));
		assertTrue(tested.getSize() == 3); 
		}
	}

	@Test
	public final void testDirectory() {
		String strRandName = System.currentTimeMillis() + "";
		Directory directory = new Directory(strRandName);
		
		assertTrue(strRandName.equals(directory.getName()));
		MyFile[] openedDirectoryFiles = (MyFile[])directory.open();
		assertTrue(countNumberOfNotNullCells(openedDirectoryFiles) == 0);
		
	}

	@Test
	public final void testAddFile() {
		Directory tested; 
		MyFile[] testedFiles;
		MyFile testedFile;
		
		{
		tested = new Directory("ABC");

		// Check we can add new files
		assertTrue(tested.addFile(textFile1));
		testedFiles = tested.openAsDirectory();
		assertTrue(countNumberOfNotNullCells(testedFiles) == 1);
		testedFile = testedFiles[0];
		testedFile.getName().equals(textFile1.getName());
		testedFile.open().equals(textFile1.open());
		assertNotSame(textFile1, testedFile);

		// Check that double adding is failing.
		assertFalse(tested.addFile(textFile1));
		testedFiles = tested.openAsDirectory();
		assertTrue(countNumberOfNotNullCells(testedFiles) == 1);
		testedFile = testedFiles[0];
		testedFile.getName().equals(textFile1.getName());
		testedFile.open().equals(textFile1.open());
		assertNotSame(textFile1, testedFile);
		
		// Check that second file adding is ok.
		assertTrue(tested.addFile(textFile2));
		testedFiles = tested.openAsDirectory();
		assertTrue(countNumberOfNotNullCells(testedFiles) == 2);
		testedFile = testedFiles[0];
		testedFile.getName().equals(textFile1.getName());
		testedFile.open().equals(textFile1.open());
		testedFile = testedFiles[1];
		testedFile.getName().equals(textFile2.getName());
		testedFile.open().equals(textFile2.open());
		assertNotSame(textFile2, testedFile);
		
		// Check that double adding is failing.
		assertFalse(tested.addFile(textFile1));
		testedFiles = tested.openAsDirectory();
		assertTrue(countNumberOfNotNullCells(testedFiles) == 2);
		testedFile = testedFiles[0];
		testedFile.getName().equals(textFile1.getName());
		testedFile.open().equals(textFile1.open());
		assertNotSame(textFile1, testedFile);
		
		// Check that double adding is failing.
		assertFalse(tested.addFile(textFile2));
		testedFiles = tested.openAsDirectory();
		assertTrue(countNumberOfNotNullCells(testedFiles) == 2);
		testedFile = testedFiles[0];
		testedFile.getName().equals(textFile1.getName());
		testedFile.open().equals(textFile1.open());
		testedFile = testedFiles[1];
		testedFile.getName().equals(textFile2.getName());
		testedFile.open().equals(textFile2.open());
		assertNotSame(textFile2, testedFile);
		}
		
		{
			Directory directory = new Directory("");
			for(int i = 0; i < 20; i++) {
				assertTrue(directory.addFile(new TextFile(i+"", "")));
			}
			
			assertFalse(directory.addFile(new TextFile(50+"", "")));
			assertFalse(directory.addFile(new TextFile(51+"", "")));
			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 2);
		}
		
		{

			Directory directory_0 = new Directory("/");
			Directory directory_1 = new Directory("/1");
			Directory directory_2 = new Directory("/1/2");

			directory_2.addFile(textFile2);
			directory_2.addFile(imageFile1);
			directory_2.addFile(imageFile2);

			directory_1.addFile(textFile1);
			directory_1.addFile(directory_2);
			
			directory_0.addFile(directory_1);
		}
	}

	@Test
	public final void testToString() {
		Directory tested;
		
		{
			tested = new Directory("ABC");

			// Check we can add new files
			assertTrue(tested.addFile(textFile1));
			assertTrue(tested.addFile(textFile2));
			assertTrue(tested.addFile(imageFile1));

			String expectedResult = "textFile1\n"
				+ "textFile2\n"
				+ "imageFile1\n";
			
			assertTrue(expectedResult.equals(tested.toString()));
		}

		{
			tested = new Directory("ABC");

			// Check we can add new files
			assertTrue(tested.addFile(textFile1));
			assertTrue(tested.addFile(textFile2));
			assertTrue(tested.addFile(imageFile1));
			assertTrue(tested.addFile(new Directory("")));
			
			String expectedResult = "textFile1\n"
				+ "textFile2\n"
				+ "imageFile1\n";
			
			assertTrue(expectedResult.equals(tested.toString()));
		}
	}

	@Test
	public final void testRemoveFile() {
		Directory tested;
		MyFile[] testedFiles;
		MyFile removedFile;

		/*
		 * Test removal of last item, which is a directory with empty name ""
		 */
		{
			tested = new Directory("ABC");

			// Check we can add new files
			assertTrue(tested.addFile(textFile1));
			assertTrue(tested.addFile(textFile2));
			assertTrue(tested.addFile(imageFile1));
			assertTrue(tested.addFile(new Directory("")));
			assertFalse(tested.addFile(new Directory("")));

			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 4);

			testedFiles = tested.openAsDirectory();
			removedFile = tested.removeFile("");
			assertTrue(removedFile.getName().equals(""));
			assertTrue(countNumberOfNotNullCells(testedFiles) == 3);

			assertTrue(testedFiles[0].getName().equals(textFile1.getName()));
			assertTrue(testedFiles[1].getName().equals(textFile2.getName()));
			assertTrue(testedFiles[2].getName().equals(imageFile1.getName()));
			assertTrue(testedFiles[3] == null);
		}

		/*
		 * Test removal of first item, which assures array shifting will occur.
		 */
		{
			tested = new Directory("ABC");

			// Check we can add new files
			assertTrue(tested.addFile(textFile1));
			assertTrue(tested.addFile(textFile2));
			assertTrue(tested.addFile(imageFile1));
			assertTrue(tested.addFile(new Directory("")));
			assertFalse(tested.addFile(new Directory("")));

			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 4);

			testedFiles = tested.openAsDirectory();
			removedFile = tested.removeFile(textFile1.getName());
			assertTrue(removedFile.getName().equals(textFile1.getName()));
			assertTrue(countNumberOfNotNullCells(testedFiles) == 3);

			assertTrue(testedFiles[0].getName().equals(textFile2.getName()));
			assertTrue(testedFiles[1].getName().equals(imageFile1.getName()));
			assertTrue(testedFiles[2].getName().equals(""));
			assertTrue(testedFiles[3] == null);
		}

		/*
		 * Test removal of middle item, which assures array shifting will occur.
		 */
		{
			tested = new Directory("ABC");

			// Check we can add new files
			assertTrue(tested.addFile(textFile1));
			assertTrue(tested.addFile(textFile2));
			assertTrue(tested.addFile(imageFile1));
			assertTrue(tested.addFile(new Directory("")));
			assertFalse(tested.addFile(new Directory("")));

			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 4);

			testedFiles = tested.openAsDirectory();
			
			
			removedFile = tested.removeFile(textFile2.getName());
			assertTrue(removedFile.getName().equals(textFile2.getName()));

			
			assertTrue(countNumberOfNotNullCells(testedFiles) == 3);

			assertTrue(testedFiles[0].getName().equals(textFile1.getName()));
			assertTrue(testedFiles[1].getName().equals(imageFile1.getName()));
			assertTrue(testedFiles[2].getName().equals(""));
			assertTrue(testedFiles[3] == null);

		}
		

		/*
		 * Test removal of first item, when directory contains 20 items
		 */
		{
			tested = new Directory("ABC");

			for(int i = 0; i < 20; i++) {
				tested.addFile(new Directory("" + i));
			}
			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 20);

			testedFiles = tested.openAsDirectory();
			
			
			removedFile = tested.removeFile("0");
			assertTrue(removedFile.getName().equals("0"));

			
			assertTrue(countNumberOfNotNullCells(testedFiles) == 19);

			assertTrue(testedFiles[0].getName().equals("1"));
			assertTrue(testedFiles[18].getName().equals("19"));
			assertTrue(testedFiles[19] == null);
		}

		
		/*
		 * Test removal of last item, when directory contains 20 items
		 */
		{
			tested = new Directory("ABC");

			for(int i = 0; i < 20; i++) {
				tested.addFile(new Directory("" + i));
			}
			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 20);

			testedFiles = tested.openAsDirectory();
			
			
			removedFile = tested.removeFile("19");
			assertTrue(removedFile.getName().equals("19"));

			
			assertTrue(countNumberOfNotNullCells(testedFiles) == 19);

			assertTrue(testedFiles[0].getName().equals("0"));
			assertTrue(testedFiles[18].getName().equals("18"));
			assertTrue(testedFiles[19] == null);
		}

		/*
		 * Test removal of non existing item.
		 */
		{
			tested = new Directory("ABC");

			for(int i = 0; i < 20; i++) {
				tested.addFile(new Directory("" + i));
			}
			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 20);

			testedFiles = tested.openAsDirectory();
			
			
			removedFile = tested.removeFile("NOFORBAR");
			assertTrue(removedFile == null);

			
			assertTrue(countNumberOfNotNullCells(testedFiles) == 20);

			assertTrue(testedFiles[0].getName().equals("0"));
			assertTrue(testedFiles[18].getName().equals("18"));
			assertTrue(testedFiles[19].getName().equals("19"));
		}

		
	}

	@Test
	public final void testSetMode() {
		Directory tested;
		MyFile[] testedFiles;
		
		{
			tested = new Directory("ABC");

			for(int i = 0; i < 5; i++) {
				assertTrue(tested.addFile(new Directory("" + i)));
			}
			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 5);

			// Define directory as not writable.
			tested.setMode(false);
			for(int i = 10; i < 15; i++) {
				assertFalse(tested.addFile(new Directory("" + i)));
			}
			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 5);

			// Define directory as writable again.
			tested.setMode(true);
			
			for(int i = 15; i < 20; i++) {
				assertTrue(tested.addFile(new Directory("" + i)));
			}
			
			testedFiles = tested.openAsDirectory();
			assertTrue(countNumberOfNotNullCells(testedFiles) == 10);
		}

	}

	static int countNumberOfNotNullCells(Object[] array) {
		int counter = 0;
		for(Object object : array) {
			if(object!=null)
				counter++;
		}
		return counter;
	}
}
