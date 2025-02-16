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
## @deftypefn {} {@var{retval} =} backward_substitution (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-10-27

function x = backward_substitution(U, b)

    [n, m] = size(U);
    if n ~= m
        error('Matrix U must be square.');
    end
    if length(b) ~= n
        error('Vector b must have the same number of rows as U.');
    end

    if any(diag(U) == 0)
        error('Das Gleichungssystem ist nicht eindeutig lösbar (Null auf der Diagonale von U).');
    end

    x = zeros(n, 1);

    for i = n:-1:1
        sum_Ux = U(i, i+1:n) * x(i+1:n);
        x(i) = (b(i) - sum_Ux) / U(i, i);
    end

    x_octave = U \ b;

    if norm(x - x_octave) > 1e-6
        warning('Die berechnete Lösung weicht von der Octave-Lösung ab.');
    else
        disp('Die Lösung wurde erfolgreich mit Octave überprüft.');
    end
end
