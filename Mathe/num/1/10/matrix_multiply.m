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
## @deftypefn {} {@var{retval} =} matrix_multiply (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-10-13

function C = matrix_multiply(A, B)

  if ~ismatrix(A) || ~isnumeric(A)
    error('Input A must be a numeric matrix or vector.');
  end
  if ~ismatrix(B) || ~isnumeric(B)
    error('Input B must be a numeric matrix or vector.');
  end

  [m, n] = size(A);
  [p, q] = size(B);

  if n ~= p
    error('Dimension mismatch');
  end

  C = zeros(m, q);

  for i = 1:m
    for j = 1:q
      sum = 0;
      for k = 1:n
        sum = sum + A(i, k) * B(k, j);
      end
      C(i, j) = sum;
    end
  end

  % Check

   C_check = A * B;
   if isequal(C, C_check)
    disp('Match');
  else
    warning('Mismatch');
  end

  disp('Result:');
  disp(C);
end

