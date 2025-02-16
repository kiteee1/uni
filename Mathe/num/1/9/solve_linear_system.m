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
## @deftypefn {} {@var{retval} =} solve_linear_system (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-10-12


function x = solve_linear_system(A_csv, b_csv)

  A = csvread(A_csv);

  b = csvread(b_csv);

  if size(b, 2) > 1
    b = b';
  end

  [m, n] = size(A);
  [p, q] = size(b);

  if m ~= p || q ~= 1
    error('Dimension mismatch');
  end

  if isempty(A)
    error('Matrix A empty');
  end

  if any(isnan(A(:))) || any(isinf(A(:)))
    error('Matrix A contains NaN or Inf values');
  end

  if any(isnan(b(:))) || any(isinf(b(:)))
    error('Vector b contains NaN or Inf values.');
  end

   if m == n
    if rank(A) < n
      error('Matrix A is singular; the system does not have a unique solution.');
    else
      x = A \ b;
    end
  else
    x = A \ b;
  end

  disp('x = ');
  disp(x);
end
