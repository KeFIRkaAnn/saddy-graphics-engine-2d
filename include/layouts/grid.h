/*! \file grid.h
    
    Describes a table, which contains cells with child nodes, arranging them in table.
    Note, that cells can contains grids inside them, allowing nesting inside of grid
 */
#pragma once
#include "../scenenode.h"
#include "../sadptrvector.h"
#include "../sadhash.h"
#include "../sadcolor.h"
#include "cell.h"

namespace sad
{
    
class Renderer;

namespace layouts
{
/*! Describes a table, which contains cells with child nodes, arranging them in table.
    Note, that cells can contains grids inside them, allowing nesting inside of grid.
    
    Note, that grid is expanded automatically, as new cells are added, so area property
    may change, due to large inner nodes.
    
    Also, you could see fixed width or fixed height and table will try to adjust to it.
    It may fail if one of nodes is too large to be fit.
 */ 
class Grid: public sad::SceneNode
{
SAD_OBJECT	
public:
    /*! Constructs a default grid with no cells
     */
    Grid();
    /*! Grid could be inherited
     */
    virtual ~Grid();
    /*! Returns cell by it's row and it's cell
        \param[in] row a row for cell
        \param[in] col a column for cell
     */
    sad::layouts::Cell* cell(unsigned int row, unsigned int col);
    /*! Sets a tree name for object with specified renderer
        \param[in] r renderer, which tree should be fetched from
        \param[in] tree_name a name for an item for object
     */
    virtual void setTreeName(sad::Renderer* r, const sad::String & tree_name);
    /*! Returns renderer for a grid
        \return renderer
     */
	// ReSharper disable once CppHidingFunction
    sad::Renderer* renderer() const;
    /*! Allows rendering of a grid
     */ 
    virtual void render();
	/*! Allows rendering of a grid with specified color
		\param[in] clr color
     */ 
    virtual void renderWithColor(const sad::AColor& clr);
    /*! Fills vector of regions with exactly one region, describing an area of grid
        \param[out] r a vector of regions
     */
    virtual void regions(sad::Vector<sad::Rect2D> & r);
    /*! Loads grid from picojson object
        \param[in] v a picojson object
        \return  whether it as successfull
     */
    virtual bool load(const picojson::value& v);	
    
    // TODO: Implement this after gettes and setters are done.
    /*! A basic schema for object
        \return a schema 
     */
    static sad::db::schema::Schema* basicSchema();
    /*! Returns schema for an object
        \return schema
     */
    virtual sad::db::schema::Schema* schema() const;	

    /*! Sets an area for table
        \param[in] r area for table
     */
    void setArea(const sad::Rect2D & r);
    /*! Returns area for label
        \return area for label
     */
    sad::Rect2D area() const;
	/*! Sets rows for grid
		\param[in] rows for grid
	 */
	void setRows(unsigned int rows);
	/*! Returns rows for grid
		\return rows for grid
	 */ 
	unsigned int rows() const;
	/*! Sets cols for grid
		\param[in] cols for grid
	 */
	void setColumns(unsigned int cols);
	/*! Returns cols for grid
		\return cols for grid
	 */ 
	unsigned int columns() const;
	/*! Sets top padding for cells. May set all cells padding's to a current value 
		if propagate is true, otherwise sets this settings for newly created cells
		\param[in] value a value for top padding
		\param[in] propagate whether we should upgrade all paddings
	 */
	void setPaddingTop(double value, bool propagate);
	/*! Sets default value for top padding of grid cells. Equivalent of call of setPaddingTop(value, false).
		\param[in] value a value
	 */
	void setDefaultPaddingTop(double value);
	/*! Returns default value for top padding of grid cells
		\return value
	 */
	double paddingTop() const;
	/*! Sets bottom padding for cells. May set all cells padding's to a current value 
		if propagate is true, otherwise sets this settings for newly created cells
		\param[in] value a value for top padding
		\param[in] propagate whether we should upgrade all paddings
	 */
	void setPaddingBottom(double value, bool propagate);
	/*! Sets default value for bottom padding of grid cells. Equivalent of call of setPaddingTop(value, false).
		\param[in] value a value
	 */
	void setDefaultPaddingBottom(double value);
	/*! Returns default value for bottom padding of grid cells
		\return value
	 */
	double paddingBottom() const;
	/*! Sets left padding for cells. May set all cells padding's to a current value 
		if propagate is true, otherwise sets this settings for newly created cells
		\param[in] value a value for top padding
		\param[in] propagate whether we should upgrade all paddings
	 */
	void setPaddingLeft(double value, bool propagate);
	/*! Sets default value for left padding of grid cells. Equivalent of call of setPaddingTop(value, false).
		\param[in] value a value
	 */
	void setDefaultPaddingLeft(double value);
	/*! Returns default value for left padding of grid cells
		\return value
	 */
	double paddingLeft() const;
	/*! Sets right padding for cells. May set all cells padding's to a current value 
		if propagate is true, otherwise sets this settings for newly created cells
		\param[in] value a value for top padding
		\param[in] propagate whether we should upgrade all paddings
	 */
	void setPaddingRight(double value, bool propagate);
	/*! Sets default value for right padding of grid cells. Equivalent of call of setPaddingTop(value, false).
		\param[in] value a value
	 */
	void setDefaultPaddingRight(double value);
	/*! Returns default value for right padding of grid cells
		\return value
	 */
	double paddingRight() const;
	/*! Sets fixed width for a grid
		\param[in] flag whether it has fixed width
	 */
	void setFixedWidth(bool flag);
	/*! Returns true if grid has fixed width
		\return true if grid has fixed width
	 */
	bool fixedWidth() const;
	/*! Sets fixed height for a table
		\param[in] flag whether it has fixed height
	 */
	void setFixedHeight(bool flag);
	/*! Returns true if grid has fixed height
		\return true if grid has fixed height
	 */
	bool fixedHeight() const;
	/*! Sets rendering color for a grid
		\param[in] clr color of a grid
	 */
	void setRenderColor(const sad::AColor& clr);
	/*! Returns rendering color for a grid
		\return rendering color
	 */
	const sad::AColor& renderColor() const;
    // TODO: Implement this
    /*! Forces grid to recompute all items for cells
     */ 
    void update();	
private:
    /*! The grid is not copyable
        \param[in] grid a grid		
     */
    Grid(const sad::layouts::Grid& grid);
    /*! The grid is not copyable
        \param[in] grid a grid
        \return self-reference
     */
    sad::layouts::Grid& operator=(const sad::layouts::Grid& grid);
    
	/*! Forces grid to update amount of cells, fixing their amount in grid
	 */
	void updateCells();
    /*! An area for a grid
     */
    sad::Rect2D m_area;
    /*! An amount of rows
     */
    unsigned int m_rows;
    /*! An amount of columns
     */
    unsigned int m_cols;
    /*! A list of cells
     */
    sad::PtrVector<sad::layouts::Cell> m_cells;
    /*! A default top padding for all cells
     */
    double m_padding_top;
    /*! A default bottom padding for all cells
     */
    double m_padding_bottom;
    /*! A default left padding for all cells
     */
    double m_padding_left;
    /*! A default right padding for all cells
     */
    double m_padding_right;	
    /*! Whether it's fixed width table.
     */
    bool m_fixed_width;
    /*! Whether it's fixed height table
     */
    bool m_fixed_height;
    /*! A rendering color for a grid
     */
    sad::AColor m_render_color;
    /*! A parent renderer for a grid
     */
    sad::Renderer * m_renderer;
    /*! Toggles loading mode on grid. If grid is loading, no update should be called
     */
    bool m_loading;	
};

}	
    
}


DECLARE_TYPE_AS_SAD_OBJECT_ENUM(sad::layouts::Grid);