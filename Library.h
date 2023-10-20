# pragma once

//CONTAINS ALL MASTER LIBRARY OPERATIONS
class Library {
	private:
        int numberOfBorrowers;

	public: 
		void beginBorrowSequence();
		void beginSearchSequence();
		void showMainMenu();
		void saveAllData();
		void beginReturnSequence();
		void beginRecordModificationSequence();

};

extern Library library;