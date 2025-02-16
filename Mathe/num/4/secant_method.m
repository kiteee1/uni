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
## @deftypefn {} {@var{retval} =} secant_method (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-11-25

function root = secant_method(f, x0, x1, tol, max_iter)
    for i = 1:max_iter
        fx0 = f(x0);
        fx1 = f(x1);
        if abs(fx1 - fx0) < eps
            error('Division by zero in Secant method');
        end
        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        if abs(x2 - x1) < tol
            root = x2;
            return;
        end
        x0 = x1;
        x1 = x2;
    end
    error('Maximum iterations reached');
end
