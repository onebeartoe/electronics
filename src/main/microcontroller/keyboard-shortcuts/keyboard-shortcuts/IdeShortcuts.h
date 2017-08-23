
/**
 * This question and answer helped me undersand how to use classes (again)
 * in C++.
 *
 *      https://stackoverflow.com/questions/318064/how-do-you-declare-an-interface-in-c
 *
 *      https://stackoverflow.com/a/318137/803890
 *
 *
 * And to achieve polymorphism, without Java interfaces, I used this as a guide.
 * 
 * 	https://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm
 * 
 */
class IdeShortcuts
{
	public:

		virtual
		KeyboardShortcut openResource();

		virtual
		KeyboardShortcut openType();// = 0;

//		KeyboardShortcut findInProjects();

//		KeyboardShortcut organizeImports();

		KeyboardShortcut gotoLastEdit(); // goto-last-edit for Atom
};
