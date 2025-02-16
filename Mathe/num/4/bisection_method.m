## Copyright (C) 2024 roman
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} bisection_method (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-11-25

function root = bisection_method(f, a, b, tol, max_iter)
    if f(a) * f(b) > 0
        error('The function must have opposite signs at a and b');
    end

    for i = 1:max_iter
        c = (a + b) / 2;
        if abs(f(c)) < tol || (b - a) / 2 < tol
            root = c;
            return;
        end
        if f(c) * f(a) < 0
            b = c;
        else
            a = c;
        end
    end
    error('Maximum iterations reached');
end
