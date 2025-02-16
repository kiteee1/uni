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
## @deftypefn {} {@var{retval} =} fit_quadratic (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-11-10

function [x1, x2, x3] = fit_quadratic(filename)
    data = csvread(filename);
    t = data(:, 1);  % Time data
    y = data(:, 2);  % Height data

    A = [ones(length(t), 1), t, t.^2];

    coeff = (A' * A) \ (A' * y);
    x1 = coeff(1);
    x2 = coeff(2);
    x3 = coeff(3);

    printf('The coefficients are:\n');
    printf('x1 = %.4f\n', x1);
    printf('x2 = %.4f\n', x2);
    printf('x3 = %.4f\n', x3);

    plot(t, y, 'r.', 'MarkerSize', 8);
    hold on;

    t_fit = linspace(min(t), max(t), 100);
    y_fit = x1 + x2 * t_fit + x3 * t_fit.^2;

    plot(t_fit, y_fit, 'b-', 'LineWidth', 2);

    xlabel('t (s)');
    ylabel('h (m)');
    legend('Data Points', 'Fitted Polynomial');
    title('Height vs Time with Fitted Quadratic Polynomial');
    hold off;
end

