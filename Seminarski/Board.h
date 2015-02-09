#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

template<class BE>
class Board;

class BoardElement: public DropTarget {
protected:
    int _row;
    int _col;
public:
    bool acceptElement(DragElement *e) {
        return elements.size()==0;
    }
    BoardElement(int row, int column) : _row(row), _col(column) {}
};

template<class BE>
class Board : public VisualElement {
protected:
    vector<vector<BE*> > elements;
    int _rows, _columns;

    void reposition() {
		int w=_width/_columns;
		int h=_height/_rows;
		for(int i=0; i<_rows; i++)
		   for(int j=0; j<_columns; j++) {
			   elements[i][j]->setPosition(_left+w*j,_top+h*i);
			   elements[i][j]->setDimension(w,h);
		   }
	}

public:
    Board(int rows=0, int columns=0) {
		if(rows*columns>0) setSize(rows,columns);
	}

    void setSize(int rows, int columns) {
        _rows=rows;
        _columns=columns;
        elements.resize(rows);
		for(int i=0; i<rows; i++) {
			elements[i].resize(columns);
			for(int j=0; j<columns; j++)
				elements[i][j]=new BE(i,j);

		}
		reposition();
    }



	BE* getElement(int y, int x) {
		return elements[y][x];
	}

	void setLeft(int left) {
		VisualElement::setLeft(left);
		reposition();
	}
	void setTop(int top) {
		VisualElement::setTop(top);
		reposition();
	}
	void setWidth(int width) {
		VisualElement::setWidth(width);
		reposition();
	}
	void setHeight(int height) {
		VisualElement::setHeight(height);
		reposition();
	}

    void paint(Canvas &c) {
        c.brush.setNoColor();
        c.rectangle(0,0,_width,_height);
    }
};




#endif // BOARD_H_INCLUDED
