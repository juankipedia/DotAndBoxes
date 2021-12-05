#ifndef dot_H
#define dot_H

# include <utility>
# include <stdexcept>
//using namespace std;

/**
 * @file dot.H
 * @brief C++ Definition of dot class.
 *
 * The dot class is the implementation of a dot in a map.
 	 The map is a matrix.
 	 A dot can have another dot on his right, left, above or below.
 	 A dot can be on a corner of the map, if is not on a corner,
 	 then it is on a border.
 * @author Codemakers.
 * @date 03/11/2016
 */

/**
 *@brief dot class
 *
 *dot class is a template.
 *@param R is the number of rows in the map.
 *@param C is the number of columns in the map.
 */
template<size_t R,size_t C> class dot
{

private:
	bool _has_left, _has_right, _has_up, _has_down;
	bool ur_corner,ul_corner,dr_corner, dl_corner, u_border, d_border, r_border, l_border;
	std::pair< size_t, size_t> position;

public:

	/**
	*@brief Basic constructor.
	*/
	dot(){/*empty*/};

	~dot(){/*empty*/};

	/**
	*@brief Constructor by position
	*
	*This constructor receives the position values of the dot
	 in the map, and makes sure that they are not out of range.
	 By the end, the flags asociated to that position are marked.
	 Important: The map is C style matrix.
	*/
	dot(std::pair<size_t, size_t> pos)
	{

		if(std::get<0>(pos) >= R or std::get<1>(pos) >= C)
			throw std::out_of_range("position out of range");

		position = pos;
		_has_down = false;
		_has_up = false;
		_has_right = false;
		_has_left = false;

		if (std::get<0>(pos) == R - 1 and std::get<1>(pos) == C - 1)
		{
			ur_corner = false;
			ul_corner = false;
			dr_corner = true;
			dl_corner = false;
			u_border = false;
			d_border = false;
			r_border = false;
			l_border = false;
			return;
		}

		if (std::get<0>(pos) == 0 and std::get<1>(pos) == C - 1)
		{
			ur_corner = true;
			ul_corner = false;
			dr_corner = false;
			dl_corner = false;
			u_border = false;
			d_border = false;
			r_border = false;
			l_border = false;
			return;
		}
		if(std::get<0>(pos)== 0 and std::get<1>(pos) == 0)
		{
			ur_corner = false;
			ul_corner = true;
			dr_corner = false;
			dl_corner = false;
			u_border = false;
			d_border = false;
			r_border = false;
			l_border = false;
			return;
		}
		if(std::get<0>(pos)== R - 1 and std::get<1>(pos) == 0)
		{
			ur_corner = false;
			ul_corner = false;
			dr_corner = false;
			dl_corner = true;
			u_border = false;
			d_border = false;
			r_border = false;
			l_border = false;
			return;
		}

		if(std::get<0>(pos) == 0)
		{
			ur_corner = false;
			ul_corner = false;
			dr_corner = false;
			dl_corner = false;
			u_border = true;
			d_border = false;
			r_border = false;
			l_border = false;
			return;
		}

		if(std::get<0>(pos) == R - 1)
		{
			ur_corner = false;
			ul_corner = false;
			dr_corner = false;
			dl_corner = false;
			u_border = false;
			d_border = true;
			r_border = false;
			l_border = false;
			return;
		}

		if(std::get<1>(pos) == C - 1)
		{
			ur_corner = false;
			ul_corner = false;
			dr_corner = false;
			dl_corner = false;
			u_border = false;
			d_border = false;
			r_border = true;
			l_border = false;
			return;
		}

		if(std::get<1>(pos) == 0)
		{
			ur_corner = false;
			ul_corner = false;
			dr_corner = false;
			dl_corner = false;
			u_border = false;
			d_border = false;
			r_border = false;
			l_border = true;
			return;
		}

		ur_corner = false;
		ul_corner = false;
		dr_corner = false;
		dl_corner = false;
		u_border = false;
		d_border = false;
		r_border = false;
		l_border = false;

		return;

	}

	/**
	*@brief Copy Constructor.
	*
	*This constructor receives a dot to be copied, this
	 constructor calls function "copy_dot()", to make copy
	 by copying every attribute.
	*/
	dot(const dot<R,C> &dot_to_copy)
	{
		copy_dot(dot_to_copy);
	}

	/**
	*@brief Copy a dot.
	*
	*This function receives a dot to be copied, function makes
	 copy by copying every attribute.
	*/
	void copy_dot(const dot<R,C> &dot_to_copy)
	{
		_has_left  = dot_to_copy._has_left;
		_has_right = dot_to_copy._has_right;
		_has_up    = dot_to_copy._has_up;
		_has_down  = dot_to_copy._has_down;
		ur_corner  = dot_to_copy.ur_corner;
		ul_corner  = dot_to_copy.ul_corner;
		dr_corner  = dot_to_copy.dr_corner;
		dl_corner  = dot_to_copy.dl_corner;
		u_border   = dot_to_copy.u_border;
		d_border   = dot_to_copy.d_border;
		r_border   = dot_to_copy.r_border;
		l_border   = dot_to_copy.l_border;
		position   = dot_to_copy.position;
	}

	/**
	*@brief operator =.
	*
	*This operator receives a dot to be copied, this
	 operator calls function "copy_dot()", to make copy
	 by copying every attribute.
	*/
	const dot<R,C>& operator = (const dot<R,C> &dot_to_copy)
	{
		copy_dot(dot_to_copy);
		return *this;
	}

	/**
	*@brief has_left() return true if there's a dot on left.
	*/
	bool has_left()
	{
		return _has_left;
	}

	/**
	*@brief has_right() return true if there's a dot on right.
	*/
	bool has_right()
	{
		return _has_right;
	}

	/**
	*@brief has_up() return true if there's a dot above.
	*/
	bool has_up()
	{
		return _has_up;
	}

	/**
	*@brief has_donw() return true if there's a dot below.
	*/
	bool has_down()
	{
		return _has_down;
	}


	/**
	*@brief is_ur_corner() return true if the dot is on the Up right corner.
	*/
	bool is_ur_corner()
	{
		return ur_corner;
	}

	/**
	*@brief is_ul_corner() return true if the dot is on the Up left corner.
	*/
	bool is_ul_corner()
	{
		return ul_corner;
	}

	/**
	*@brief is_dr_corner() return true if the dot is on the Down right corner.
	*/
	bool is_dr_corner()
	{
		return dr_corner;
	}

	/**
	*@brief is_dl_corner() return true if the dot is on the Down left corner.
	*/
	bool is_dl_corner()
	{
		return dl_corner;
	}


	/**
	*@brief is_u_border() return true if the dot is on the Up border.
	*/
	bool is_u_border()
	{
		return u_border;
	}

	/**
	*@brief is_d_border() return true if the dot is on the down  border.
	*/
	bool is_d_border()
	{
		return d_border;
	}

	/**
	*@brief is_l_border() return true if the dot is on the left  border.
	*/
	bool is_l_border()
	{
		return l_border;
	}

	/**
	*@brief is_u_border() return true if the dot is on the right border.
	*/
	bool is_r_border()
	{
		return r_border;
	}

	/**
	*@brief get_position() return the position of the dot on the map.
	*/
	const std::pair<size_t, size_t> & get_position()
	{
		return position;
	}

	/**
	*@brief get_pos() return the position of the dot on the map.
	*/
	const std::pair<size_t, size_t> & get_pos() const
	{
		return position;
	}

	/**
	*@brief mark_left() Set has_left true.
	*/
	void mark_left()
	{
		_has_left = true;
	}

	/**
	*@brief mark_left() Set has_right true.
	*/
	void mark_right()
	{
		_has_right = true;
	}

	/**
	*@brief mark_left() Set has_up true.
	*/
	void mark_up()
	{
		_has_up = true;
	}

	/**
	*@brief mark_left() Set has_down true.
	*/
	void mark_down()
	{
		_has_down = true;
	}

	/**
	*@brief set_left(bool l).
	*/
	void set_left(bool l)
	{
		_has_left = l;
	}

	/**
	*@brief set_right(bool r).
	*/
	void set_right(bool r)
	{
		_has_right = r;
	}

	/**
	*@brief set_up(bool u).
	*/
	void set_up(bool u)
	{
		_has_up = u;
	}

	/**
	*@brief set_down(bool l).
	*/
	void set_down(bool d)
	{
		_has_down = d;
	}

	/**
	*@brief is_full() Return true if the dot is completely surrounded.
	*/
	bool is_full()
	{
		if(ur_corner)
			return _has_down and _has_left;

		if(ul_corner)
			return _has_down and _has_right;

		if(dr_corner)
			return _has_left and _has_up;

		if(dl_corner)
			return _has_right and _has_up;

		if(u_border)
			return _has_down and _has_left and _has_right;

		if(d_border)
			return _has_up and _has_left and _has_right;

		if(l_border)
			return _has_right and _has_up and _has_down;

		if(r_border)
			return _has_left and _has_up and _has_down;

		return _has_down and _has_up and _has_right and _has_left;
	}

	/**
	*@brief reset_dot() Restore the dot.
	*
	*Restore the dot to a no surrounded dot, wich means that
	 has not another dot next to him.
	*/
	void reset_dot()
	{
		_has_left = false;
		_has_right = false;
		_has_down = false;
		_has_up = false;
	}

	/**
	*@brief tells if a dot is equal to another by comparing its
	 positions.
	*
	*@returns true if their positions are equal.
	*/
	bool operator == (const dot & dot_)
	{
		return get_pos() == dot_.get_pos();
	}

};

#endif
