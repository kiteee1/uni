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
## @deftypefn {} {@var{retval} =} power_iteration (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-11-10

function [eigenvalue, eigenvector] = power_iteration(A, tolerance, max_iters)

    n = size(A, 1);
    eigenvector = rand(n, 1);
    eigenvector = eigenvector / norm(eigenvector);

    for k = 1:max_iters
        new_vector = A * eigenvector;

        new_vector = new_vector / norm(new_vector);

        if norm(new_vector - eigenvector) < tolerance
            break;
        end

        eigenvector = new_vector;
    end

    eigenvalue = (eigenvector' * A * eigenvector) / (eigenvector' * eigenvector);
end
